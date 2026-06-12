## Problem

https://leetcode.com/problems/range-sum-query-mutable/description/

Given an integer array `nums`, handle multiple queries of the following types:

1. **Update** the value of an element in `nums`.
2. **Calculate the sum** of the elements between indices `left` and `right` inclusive.

Implement the `NumArray` class:
- `NumArray(int[] nums)` — initializes the object with the integer array `nums`.
- `void update(int index, int val)` — updates `nums[index]` to `val`.
- `int sumRange(int left, int right)` — returns the sum of `nums[left] + ... + nums[right]`.

**Example:**
```
Input:  ["NumArray", "sumRange", "update", "sumRange"]
        [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
Output: [null, 9, null, 8]

NumArray([1, 3, 5])  →  initial array
sumRange(0, 2)       →  1 + 3 + 5 = 9
update(1, 2)         →  nums = [1, 2, 5]
sumRange(0, 2)       →  1 + 2 + 5 = 8
```

**Constraints:**
- `1 <= nums.length <= 3 * 10⁴`
- `-100 <= nums[i] <= 100`
- At most `3 * 10⁴` calls to `update` and `sumRange`.

---

## Observations

- A **naïve prefix-sum array** answers `sumRange` in $O(1)$, but every `update` then requires $O(n)$ time to rebuild the prefix sums — too slow under frequent mutations.

- A **naïve update** (mutate the raw array and loop over the range) makes `update` $O(1)$ but `sumRange` $O(n)$ — also too slow.

- We need a data structure that supports **both** operations faster than $O(n)$.

- The **Binary Indexed Tree (BIT)**, also called a **Fenwick Tree**, is the perfect fit:
  - `update`: $O(\log n)$
  - `sumRange`: $O(\log n)$
  - Space: $O(n)$

- A **Segment Tree** is an alternative with the same complexities, but BIT is simpler to implement and has a smaller constant factor for this problem.

- Key insight for `update`: instead of storing the absolute value in the BIT, we store a **delta** (the difference between the new and old value). This lets us reuse the same `add` primitive for both initialization and updates.

---

## Solution Explanation

### Binary Indexed Tree (Fenwick Tree)

A BIT stores **partial sums** in a clever way using the binary representation of indices, allowing both point updates and prefix-sum queries in $O(\log n)$.

#### Internal 1-indexed layout

BIT indices are **1-indexed** internally. An element at BIT index `i` is responsible for the range of the original array of length equal to the **lowest set bit** of `i`:

$$\text{responsibility length of } i = i \mathbin{\&} (-i)$$

This means:
- Index `1` (binary `001`) covers 1 element.
- Index `2` (binary `010`) covers 2 elements.
- Index `4` (binary `100`) covers 4 elements.
- Index `6` (binary `110`) covers 2 elements (the lowest set bit is `010 = 2`).

#### `add(idx, val)` — point update

```
idx += 1          # shift to 1-indexed
while idx <= n:
    tree[idx] += val
    idx += (idx & -idx)   # move to the next responsible ancestor
```

Starting at position `idx`, we walk **upward** by adding the lowest set bit. Every node we visit is a partial-sum bucket that covers `idx`, so all of them must be updated.

#### `query(idx)` — prefix sum [0 … idx]

```
idx += 1          # shift to 1-indexed
s = 0
while idx > 0:
    s += tree[idx]
    idx -= (idx & -idx)   # strip the lowest set bit → move to parent prefix
```

Starting at `idx`, we walk **downward** by stripping the lowest set bit, accumulating the partial sums that together cover the range $[0, \text{idx}]$.

#### `range_query(left, right)` — range sum

A range sum is expressed as the difference of two prefix sums:

$$\text{sumRange}(l, r) = \text{query}(r) - \text{query}(l - 1)$$

The edge case `left == 0` is handled cleanly because `query(-1)` short-circuits to `0` in the loop (the loop condition `idx > 0` fails immediately after `idx` becomes 0).

#### `NumArray` wrapper

```python
def __init__(self, nums):
    self.nums = nums[:]          # keep a copy to track current values
    self.bit = BIT(len(nums))
    for i, val in enumerate(nums):
        self.bit.add(i, val)     # build BIT in O(n log n)

def update(self, index, val):
    delta = val - self.nums[index]   # compute change
    self.nums[index] = val           # keep copy in sync
    self.bit.add(index, delta)       # apply delta, not absolute value

def sumRange(self, left, right):
    return self.bit.range_query(left, right)
```

The copy `self.nums` is essential: without it, we cannot compute the **delta** needed by `update`, because the BIT itself does not store original values.

### Complexity

| Operation    | Time        | Space |
|-------------|-------------|-------|
| `__init__`   | $O(n \log n)$ | $O(n)$ |
| `update`     | $O(\log n)$  | $O(1)$ |
| `sumRange`   | $O(\log n)$  | $O(1)$ |

---

## Solution

```python
class BIT:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)
    
    def add(self, idx, val):
        idx += 1
        while idx <= self.n:
            self.tree[idx] += val
            idx += (idx & -idx)
    
    def query(self, idx):
        idx += 1
        s = 0
        while idx > 0:
            s += self.tree[idx]
            idx -= (idx & -idx)
        return s
    
    def range_query(self, left, right):
        if left > right:
            return 0
        return self.query(right) - self.query(left - 1)

class NumArray:

    def __init__(self, nums: List[int]):
        self.n = len(nums)
        self.nums = nums[:]
        self.bit = BIT(self.n)
        for i, val in enumerate(nums):
            self.bit.add(i, val)

    def update(self, index: int, val: int) -> None:
        delta = val - self.nums[index]
        self.nums[index] = val
        self.bit.add(index, delta)

    def sumRange(self, left: int, right: int) -> int:
        return self.bit.range_query(left, right)
```
