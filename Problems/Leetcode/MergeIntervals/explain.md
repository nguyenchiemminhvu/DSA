## Problem

https://leetcode.com/problems/merge-intervals/description

# Merge Intervals

## Problem

https://leetcode.com/problems/merge-intervals/description

Given an array of intervals where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals and return an array of the non-overlapping intervals that cover all the intervals in the input.

### Examples

**Example 1:**
- **Input:** `intervals = [[1,3],[2,6],[8,10],[15,18]]`
- **Output:** `[[1,6],[8,10],[15,18]]`
- **Explanation:** Since intervals `[1,3]` and `[2,6]` overlap, merge them into `[1,6]`.

**Example 2:**
- **Input:** `intervals = [[1,4],[4,5]]`
- **Output:** `[[1,5]]`
- **Explanation:** Intervals `[1,4]` and `[4,5]` are considered overlapping.

**Example 3:**
- **Input:** `intervals = [[4,7],[1,4]]`
- **Output:** `[[1,7]]`
- **Explanation:** Intervals `[1,4]` and `[4,7]` are considered overlapping.

### Constraints

- `1 <= intervals.length <= 10^4`
- `intervals[i].length == 2`
- `0 <= start_i <= end_i <= 10^4`

---

## Observations

1. **Sorting is Key:** Two intervals can only be compared meaningfully if we know their relative position on the number line. Sorting by the start time ensures we process intervals in order.

2. **Overlapping Condition:** Two adjacent intervals `[a, b]` and `[c, d]` (where `a <= c` after sorting) overlap if and only if `c <= b`. This includes the case where they touch at a single point (e.g., `[1,4]` and `[4,5]`).

3. **Merging Strategy:** When two intervals overlap, the merged interval spans from the start of the first to the maximum of both ends: `[a, max(b, d)]`.

4. **Greedy Approach:** We can solve this by iterating through sorted intervals and maintaining the last merged interval. When we encounter an overlapping interval, we extend the end of the previous interval. When we encounter a non-overlapping interval, we add the previous one to results and start tracking the new one.

5. **No Unnecessary Comparisons:** After sorting, we only need to compare consecutive intervals since if interval A overlaps with C, and C is between A and B (in sorted order), we'll handle the overlap when comparing A with B or C with B.

6. **Edge Cases:**
   - Single interval: Already merged (return as-is)
   - All intervals overlap: Merge into one
   - No intervals overlap: Return all (just sorted)
   - Touching endpoints: Should be merged (`[1,4]` and `[4,5]` → `[1,5]`)

---

## Solution Approach

### Algorithm: Sort and Merge

```python
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        # Step 1: Sort intervals by start time (and end time as tiebreaker)
        intervals.sort(key=lambda x: (x[0], x[1]))
        
        # Step 2: Initialize result with the first interval
        res = [intervals[0]]
        
        # Step 3: Iterate through remaining intervals
        for i in range(1, len(intervals)):
            prev = res[-1]  # Get the last merged interval
            
            # Step 4: Check if current interval overlaps with previous
            if intervals[i][0] <= prev[1]:
                # Merge: extend the end to the maximum
                prev[1] = max(prev[1], intervals[i][1])
            else:
                # No overlap: add current interval as a new merged group
                res.append(intervals[i])
        
        return res
```

### Step-by-Step Walkthrough

**Example:** `intervals = [[1,3],[2,6],[8,10],[15,18]]`

1. **Sort:** Already sorted → `[[1,3],[2,6],[8,10],[15,18]]`

2. **Initialize:** `res = [[1,3]]`

3. **Iteration 1 (i=1, interval=[2,6]):**
   - `prev = [1,3]`, check if `2 <= 3`? **Yes, overlaps**
   - Merge: `prev[1] = max(3, 6) = 6`
   - `res = [[1,6]]`

4. **Iteration 2 (i=2, interval=[8,10]):**
   - `prev = [1,6]`, check if `8 <= 6`? **No, no overlap**
   - Append new interval: `res = [[1,6],[8,10]]`

5. **Iteration 3 (i=3, interval=[15,18]):**
   - `prev = [8,10]`, check if `15 <= 10`? **No, no overlap**
   - Append new interval: `res = [[1,6],[8,10],[15,18]]`

6. **Return:** `[[1,6],[8,10],[15,18]]` ✓

### Complexity Analysis

- **Time Complexity:** $O(n \log n)$ where $n$ is the number of intervals
  - Sorting: $O(n \log n)$
  - Single pass through sorted intervals: $O(n)$
  - Total: $O(n \log n)$

- **Space Complexity:** $O(1)$ or $O(n)$
  - If we don't count the output array: $O(1)$ (only modifying input/output)
  - If we count the output array: $O(n)$

### Key Insights

1. **Why Sort Works:** After sorting by start time, overlapping intervals must be adjacent. We never need to look back further than the immediately previous merged interval.

2. **In-place Modification:** We modify `prev[1]` directly instead of creating new intervals, which is efficient and allowed in Python lists.

3. **Greedy Correctness:** At each step, merging overlapping intervals is optimal because:
   - It doesn't prevent future merges
   - It reduces the total number of intervals
   - It correctly extends the coverage to include all points from both intervals

4. **Edge Case Handling:**
   - **Touching endpoints** (`[1,4]` and `[4,5]`): The condition `intervals[i][0] <= prev[1]` (4 <= 4) is True, so they merge correctly
   - **Nested intervals** (`[1,5]` and `[2,3]`): The condition `2 <= 5` is True, and `max(5, 3) = 5` keeps the correct range

### Alternative Approaches

**Option 1: Using a List and Tracking Index (if modifying input is not desired)**
```python
def merge(self, intervals: List[List[int]]) -> List[List[int]]:
    intervals.sort()
    merged = []
    for start, end in intervals:
        if merged and start <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])
    return merged
```

**Option 2: Using Tuple Unpacking (more Pythonic)**
```python
def merge(self, intervals: List[List[int]]) -> List[List[int]]:
    intervals.sort()
    res = []
    for start, end in intervals:
        if res and start <= res[-1][1]:
            res[-1][1] = max(res[-1][1], end)
        else:
            res.append([start, end])
    return res
```

---

## Tags

- **Difficulty:** Medium
- **Category:** Interval Problems, Greedy Algorithm, Sorting
- **Company Tags:** Amazon, Facebook, Google, Microsoft
- **Key Concepts:** 
  - Sorting
  - Greedy Algorithm
  - Two-pointer technique (comparing adjacent elements)
  - Array manipulation

## Observations

## Solution

# Tags

