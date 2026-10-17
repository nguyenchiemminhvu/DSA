## Problem

https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/description/

You are given an array `nums` of **distinct** positive integers. Sort the array in **increasing** order based on the sum of the digits of each number. If two numbers have the same digit sum, the **smaller** number appears first.

Return the **minimum** number of swaps required to rearrange `nums` into this sorted order.

A **swap** exchanges the values at two distinct positions in the array.

**Example 1:**
```
Input: nums = [37,100]
Output: 1
Explanation: Digit sums are [10, 1]. Sorted order is [100, 37]. Swap 37 with 100.
```

**Example 2:**
```
Input: nums = [22,14,33,7]
Output: 0
Explanation: Digit sums are [4, 5, 6, 7]. The array is already sorted.
```

**Example 3:**
```
Input: nums = [18,43,34,16]
Output: 2
Explanation: Digit sums are [9, 7, 7, 7]. Sorted order is [16, 34, 43, 18].
Swap 18 with 16, then swap 43 with 34.
```

**Constraints:**
- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^9`
- `nums` consists of **distinct** positive integers.

## Observations

1. **Unique target**: The sort key is the pair (digit sum, value). Because all values are distinct, there are no ties, so the sorted array (the target) is unique.

2. **Permutation view**: Only the positions of the elements matter. The problem reduces to turning the original array into the target array using the fewest swaps.

3. **Arbitrary swaps**: A swap can exchange any two positions, not only adjacent ones. Counting inversions (as in bubble sort) does not give the minimum.

4. **Cycles decide the answer**: The minimum number of swaps depends only on how the permutation splits into cycles.

## Ideas

### Idea 1: Brute force (BFS over arrays)

Try every sequence of swaps until the sorted array appears. The number of reachable arrays grows factorially, so this is infeasible for $n$ up to $10^5$.

### Idea 2: Sort, then count cycles (chosen)

1. Compute the digit sum of each number.
2. Sort the indices by (digit sum, value) to get the target order.
3. Treat the mapping from target position to original position as a permutation.
4. Split the permutation into disjoint cycles. A cycle of length $L$ needs exactly $L - 1$ swaps, so the answer is $\sum (L - 1)$.

## Cycle Technique in Detail

### Step 1: Build the permutation

Let `pairs` be the list of `(digit sum, value, original index)` sorted ascending. After sorting, `pairs[i][2]` is the original index of the element that must end up at position `i`. Call this array `src`. Since every original index appears exactly once, `src` is a permutation of `0..n-1`.

For Example 3:

| Sorted position `i` | Value that belongs here | Original index `src[i]` |
|---|---|---|
| 0 | 16 | 3 |
| 1 | 34 | 2 |
| 2 | 43 | 1 |
| 3 | 18 | 0 |

So `src = [3, 2, 1, 0]`.

### Step 2: Follow each cycle

Start at an unvisited index `i` and repeatedly jump to `src[j]`:

```
i -> src[i] -> src[src[i]] -> ... -> back to i
```

All indices on this path form one cycle. Mark them visited. Indices that already point to themselves (`src[i] == i`) are fixed points, which are cycles of length 1 and need 0 swaps.

### Step 3: Why a cycle of length L needs L - 1 swaps

Take the array `[2, 3, 1]`, whose target is `[1, 2, 3]`. The positions form one cycle of length 3.

- Position 0 needs the value 1, which sits at position 2. Swap positions 0 and 2: `[1, 3, 2]`. Position 0 is now correct.
- Position 1 needs the value 2, which sits at position 2. Swap positions 1 and 2: `[1, 2, 3]`. Positions 1 and 2 are now correct.

Two swaps for a cycle of length 3. Each swap places at least one element permanently, and the final swap fixes two positions at once, so the cost is $L - 1$.

### Step 4: Why this is the minimum

Model the permutation as a graph with $n$ nodes. The sorted array has $n$ cycles, all fixed points. Let $c$ be the number of cycles in the current array.

- Swapping two positions in the **same** cycle splits that cycle into two, so $c$ increases by 1.
- Swapping two positions in **different** cycles merges them, so $c$ decreases by 1.

Reaching $n$ cycles from $c$ requires at least $n - c$ swaps. The cycle method always splits, so it uses exactly $n - c = \sum (L - 1)$ swaps, which is optimal.

### Step 5: Walkthrough for Example 3

`src = [3, 2, 1, 0]`

```
i = 0: 0 -> 3 -> 0          cycle length 2, add 1   (res = 1)
i = 1: 1 -> 2 -> 1          cycle length 2, add 1   (res = 2)
i = 2: already visited
i = 3: already visited

Result: 2
```

Applying the swaps to the array `[18, 43, 34, 16]`:

```
Swap positions 0 and 3: [16, 43, 34, 18]
Swap positions 1 and 2: [16, 34, 43, 18]   (sorted)
```

## Solution

```python
from typing import List

class Solution:
    def minSwaps(self, nums: List[int]) -> int:
        n = len(nums)

        def sum_digits(val: int):
            s = 0
            while val:
                s += (val % 10)
                val //= 10
            return s

        pairs = [[sum_digits(val), val, i] for i, val in enumerate(nums)]
        pairs.sort()

        res = 0
        visited = {i: False for i in range(n)}
        for i in range(n):
            if pairs[i][2] == i:
                continue

            cycle_size = 0
            j = i
            while not visited[j]:
                visited[j] = True
                j = pairs[j][2]
                cycle_size += 1

            if cycle_size > 0:
                res += cycle_size - 1

        return res
```

**Complexity Analysis:**

- **Time Complexity**: $O(n \log n)$
  - Digit sum computation: $O(n \cdot D)$, where $D \le 10$ is the number of digits
  - Sorting the pairs: $O(n \log n)$
  - Cycle traversal: $O(n)$, since each index is visited once
- **Space Complexity**: $O(n)$ for `pairs` and `visited`

# Tags

`Sorting` `Permutation` `Cycle Decomposition` `Greedy` `Array`
