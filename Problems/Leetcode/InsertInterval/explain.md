## Problem

https://leetcode.com/problems/insert-interval/description

You are given an array of **non-overlapping intervals** where `intervals[i] = [start_i, end_i]` represents the start and end of the ith interval, and `intervals` is sorted in ascending order by `start_i`. You are also given an interval `newInterval = [start, end]`.

Insert `newInterval` into `intervals` such that:
1. `intervals` is still sorted in ascending order by `start_i`
2. `intervals` still does not have any overlapping intervals (merge overlapping intervals if necessary)

Return `intervals` after the insertion.

**Constraints:**
- `0 <= intervals.length <= 10^4`
- `intervals[i].length == 2`
- `0 <= start_i <= end_i <= 10^5`
- `intervals` is sorted by `start_i` in ascending order
- `newInterval.length == 2`
- `0 <= start <= end <= 10^5`

**Examples:**

Example 1:
```
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
```

Example 2:
```
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
```

## Observations

1. **Initial State**: The input `intervals` array is already sorted and has no overlapping intervals. We need to insert `newInterval` while maintaining these properties.

2. **Key Insight**: Instead of handling the insertion separately from merging, we can append `newInterval` to the array and then treat this as a **merge intervals problem** on the entire array.

3. **Sorting After Insertion**: Since `newInterval` might not be in the correct sorted position, we need to restore the sorted property. However, we can use a bubble-sort-like approach to move it to its correct position by comparing with adjacent elements.

4. **Merge Strategy**: Once `newInterval` is in the correct position (maintaining sorted order), we can apply the standard merge intervals algorithm:
   - Iterate through intervals
   - If the current interval overlaps with the previous one, merge them by extending the end point
   - Otherwise, add it as a new interval to the result

5. **Overlap Condition**: Two intervals overlap if `current[start] <= previous[end]`. In case of overlap, we take the maximum of the two end points: `max(previous[end], current[end])`.

6. **Time Complexity**: 
   - Inserting and sorting: O(n) in the worst case (bubble sort)
   - Merging: O(n)
   - **Total: O(n)**

7. **Space Complexity**: O(n) for the output array (not counting the output).

## Solution

```python
class Solution:
    def insert(self, intervals: List[List[int]], new_interval: List[int]) -> List[List[int]]:
        # Step 1: Append the new interval to the list
        intervals.append(new_interval)
        
        # Step 2: Bubble the new interval to its correct sorted position
        prev = len(intervals) - 2
        while prev >= 0 and intervals[prev][0] > intervals[prev + 1][0]:
            # Swap adjacent intervals
            intervals[prev], intervals[prev + 1] = intervals[prev + 1], intervals[prev]
            prev -= 1
        
        # Step 3: Merge overlapping intervals (standard merge intervals algorithm)
        res = [intervals[0]]
        for i in range(1, len(intervals)):
            prev = res[-1]
            # Check if current interval overlaps with the last interval in result
            if intervals[i][0] <= prev[1]:
                # Merge: extend the end point
                prev[1] = max(prev[1], intervals[i][1])
            else:
                # No overlap: add as new interval
                res.append(intervals[i])
        
        return res
```

### Step-by-Step Explanation

**Step 1: Append New Interval**
```python
intervals.append(new_interval)
```
We add `newInterval` to the end of the `intervals` array. This guarantees we won't lose it during the merge process.

**Step 2: Restore Sorted Order**
```python
prev = len(intervals) - 2
while prev >= 0 and intervals[prev][0] > intervals[prev + 1][0]:
    intervals[prev], intervals[prev + 1] = intervals[prev + 1], intervals[prev]
    prev -= 1
```
Since we appended `newInterval` at the end, the array may no longer be sorted. We use a simple bubble-sort approach to move it to its correct position by comparing start points and swapping as needed.

**Step 3: Merge Overlapping Intervals**
```python
res = [intervals[0]]
for i in range(1, len(intervals)):
    prev = res[-1]
    if intervals[i][0] <= prev[1]:
        prev[1] = max(prev[1], intervals[i][1])
    else:
        res.append(intervals[i])
```
This is the standard merge intervals algorithm:
- Start with the first interval in the result
- For each subsequent interval:
  - If it overlaps with the last interval in the result (`current_start <= last_end`), merge them by updating the end point
  - Otherwise, add it as a new interval

### Example Walkthrough

**Example 2**: `intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]]`, `newInterval = [4,8]`

1. **After append**: `[[1,2],[3,5],[6,7],[8,10],[12,16],[4,8]]`

2. **After sorting** (bubble the last element):
   - Compare `[12,16]` and `[4,8]`: 12 > 4, swap → `[[1,2],[3,5],[6,7],[8,10],[4,8],[12,16]]`
   - Compare `[8,10]` and `[4,8]`: 8 > 4, swap → `[[1,2],[3,5],[6,7],[4,8],[8,10],[12,16]]`
   - Compare `[6,7]` and `[4,8]`: 6 > 4, swap → `[[1,2],[3,5],[4,8],[6,7],[8,10],[12,16]]`
   - Compare `[3,5]` and `[4,8]`: 3 < 4, stop

3. **After merging**:
   - Start: `res = [[1,2]]`
   - Process `[3,5]`: 3 > 2, no overlap → `res = [[1,2],[3,5]]`
   - Process `[4,8]`: 4 <= 5, overlap! Merge to `[3, max(5,8)] = [3,8]` → `res = [[1,2],[3,8]]`
   - Process `[6,7]`: 6 <= 8, overlap! Merge to `[3, max(8,7)] = [3,8]` → `res = [[1,2],[3,8]]`
   - Process `[8,10]`: 8 <= 8, overlap! Merge to `[3, max(8,10)] = [3,10]` → `res = [[1,2],[3,10]]`
   - Process `[12,16]`: 12 > 10, no overlap → `res = [[1,2],[3,10],[12,16]]`

**Result**: `[[1,2],[3,10],[12,16]]` ✓

# Tags
#intervals #greedy #merge #sorting #medium

