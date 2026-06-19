## Problem

https://leetcode.com/problems/find-median-from-data-stream

```
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.

Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10^-5 of the actual answer will be accepted.

Example 1:

Input:
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]

Output:
[null, null, null, 1.5, null, 2.0]

Explanation:
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr = [1, 2, 3]
medianFinder.findMedian(); // return 2.0

Constraints:

-10^5 <= num <= 10^5
There will be at least one element in the data structure before calling findMedian.
At most 5 * 10^4 calls will be made to addNum and findMedian.
```

## Observations

1. **Median Requires Order**: To find the median, we need the data sorted. Inserting into a sorted array each time costs O(n) per insertion, which is too slow for a stream. We need a smarter structure that maintains order efficiently.

2. **The "Two Halves" Insight**: The median only depends on the element(s) near the middle of the sorted list. If we split all numbers into a **lower half** and an **upper half**, the median is:
   - The max of the lower half (odd total count), or
   - The average of the max of the lower half and the min of the upper half (even total count).

3. **Max-Heap + Min-Heap is the Perfect Fit**:
   - A **max-heap** (`left`) holds the lower half, giving O(1) access to its maximum (the largest small number).
   - A **min-heap** (`right`) holds the upper half, giving O(1) access to its minimum (the smallest large number).
   - All elements in `left` are ≤ all elements in `right`.
   - Together, the two heap tops are the only values we ever need for the median.

4. **Balance Invariant**: We enforce that `len(left) == len(right)` (even total) or `len(left) == len(right) + 1` (odd total, median is `left[0]`). This ensures the heap tops always represent the median position(s).

5. **Insertion Strategy**:
   - A new number ≤ top of `left` belongs to the lower half → push to `left`.
   - A new number > top of `left` belongs to the upper half → push to `right`.
   - After every insertion, re-balance the two heaps if the size difference exceeds 1.

6. **Python's `heapq` is a Min-Heap**: To simulate a max-heap for `left`, we store negated values (`-num`). The "maximum" of the lower half is then `-left[0]`.

7. **Complexity**:
   - `addNum`: O(log n) — heap push/pop.
   - `findMedian`: O(1) — only looks at the heap tops.
   - Space: O(n) — all n elements are stored across the two heaps.

## Solution

### Algorithm Overview

The solution maintains two heaps that together represent the sorted data stream split at the median point:

```
Lower half (max-heap)  |  Upper half (min-heap)
  left = [... max]     |  right = [min ...]
```

The key invariant is:
- Every element in `left` ≤ every element in `right`.
- `len(left) == len(right)` or `len(left) == len(right) + 1`.

This allows the median to be read in O(1) at any time.

### Step-by-Step Explanation

#### 1. Initialization
```python
def __init__(self):
    self.left = []  # max heap (stored as negated values)
    self.right = [] # min heap
```
Both heaps start empty.

#### 2. Adding a Number

```python
def addNum(self, num: int) -> None:
    if not self.left:
        heapq.heappush(self.left, -num)
    else:
        if num <= -self.left[0]:
            heapq.heappush(self.left, -num)
        else:
            heapq.heappush(self.right, num)
    
    self.__balancing()
```

**Routing logic:**
- If `left` is empty, push to `left` (first element always starts there).
- If `num ≤ max(left)`, the number belongs to the lower half → push to `left`.
- Otherwise, the number belongs to the upper half → push to `right`.

After routing, call `__balancing()` to restore the size invariant.

#### 3. Balancing

```python
def __balancing(self):
    while len(self.right) > len(self.left):
        heapq.heappush(self.left, -heapq.heappop(self.right))
    
    while len(self.left) > len(self.right) + 1:
        heapq.heappush(self.right, -heapq.heappop(self.left))
```

- **`right` too large**: Pop the minimum of `right` and push it to `left` (it becomes the new lower-half maximum).
- **`left` too large**: Pop the maximum of `left` (negate it back) and push it to `right`.

This ensures the size invariant is always restored in O(log n).

#### 4. Finding the Median

```python
def findMedian(self) -> float:
    if not self.left:
        return 0.0
    
    if len(self.left) == len(self.right):
        return (-self.left[0] + self.right[0]) / 2.0
    
    return float(-self.left[0])
```

- **Even count** (`left` and `right` equal size): median = average of both heap tops.
- **Odd count** (`left` has one more): median = top of `left` (the true middle element).

### Visual Example

Trace the example `[1, 2, 3]`:

```
addNum(1):
  left is empty → push to left
  left  = [1]  (stored as [-1])
  right = []
  Balance: sizes [1, 0] → OK
  
  Median candidates: left_top=1

addNum(2):
  2 > max(left)=1 → push to right
  left  = [1]  (stored as [-1])
  right = [2]
  Balance: sizes [1, 1] → OK

  findMedian(): sizes equal → (1 + 2) / 2 = 1.5 ✓

addNum(3):
  3 > max(left)=1 → push to right
  left  = [1]  (stored as [-1])
  right = [2, 3]
  Balance: len(right)=2 > len(left)=1
    → pop min of right (2), push to left
  left  = [1, 2]  (stored as [-2, -1])
  right = [3]
  Balance: len(left)=2 == len(right)+1=2 → OK

  findMedian(): len(left) > len(right) → return left_top = 2.0 ✓
```

### Heap State Visualization

After inserting `[1, 2, 3, 4, 5]` one by one:

```
Step  | Added | left (max-heap)  | right (min-heap) | Median
------|-------|------------------|------------------|-------
  1   |   1   | [1]              | []               | 1.0
  2   |   2   | [1]              | [2]              | 1.5
  3   |   3   | [1, 2]           | [3]              | 2.0
  4   |   4   | [1, 2]           | [3, 4]           | 2.5
  5   |   5   | [1, 2, 3]        | [4, 5]           | 3.0
```

The heaps always stay balanced, and the median is always at the boundary between them.

### Why the Balancing Direction Matters

The balancing moves elements from `right` to `left` first, before moving from `left` to `right`. This guarantees:
- `left` always holds the extra element when total count is odd.
- `findMedian()` only needs to check `left[0]` for the odd case, keeping logic simple.

### Follow-up Questions

**Q: If all numbers are in [0, 100], how would you optimize?**

Use a **frequency array** of size 101. Track total count and update cumulative sums to find the median in O(100) = O(1) time. Each `addNum` is O(1) and `findMedian` scans at most 101 buckets.

**Q: If 99% of numbers are in [0, 100], how would you optimize?**

Combine both approaches:
- Use a frequency array for numbers in [0, 100].
- Use two heaps (or sorted containers) for the outliers (< 0 or > 100).
- Track total count. When finding the median, determine whether the median position falls in the [0, 100] range or in the outlier heaps, and query accordingly.

### Complexity Analysis

- **Time Complexity**:
  - `addNum`: O(log n) — each heap push/pop is O(log n).
  - `findMedian`: O(1) — reads only the heap tops.
  
- **Space Complexity**: O(n) — all n inserted elements are stored across the two heaps.

### Common Mistakes to Avoid

1. **Forgetting to negate values for `left`**: Python's `heapq` is a min-heap. Without negation, `left[0]` would be the minimum, not the maximum of the lower half.
2. **Balancing after every insertion, not just when unbalanced**: Always rebalance after adding; missing a single step breaks the invariant for all future queries.
3. **Off-by-one in balance condition**: `left` should be allowed to have exactly one more element than `right` (for odd totals). Allowing two more would misplace the median.
4. **Not handling the empty `left` case in `findMedian`**: If no numbers have been added yet, return a default (e.g., `0.0`).

## Tags

heap, two heaps, design, data stream, priority queue
