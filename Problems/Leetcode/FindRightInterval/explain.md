## Problem

https://leetcode.com/problems/find-right-interval/description/

Given an array of intervals where `intervals[i] = [start_i, end_i]` and each `start_i` is unique, find the "right interval" for each interval.

The **right interval** for interval `i` is an interval `j` such that:
- `start_j >= end_i` 
- `start_j` is **minimized** (smallest possible value that satisfies the condition)
- Note that `i` may equal `j` (an interval can be its own right interval)

Return an array where each index contains the original index of the right interval, or `-1` if no right interval exists.

**Examples:**
- `intervals = [[1,2]]` → `[-1]` (only one interval, no right interval exists)
- `intervals = [[3,4],[2,3],[1,2]]` → `[-1,0,1]`
  - `[3,4]`: no interval starts at >= 4
  - `[2,3]`: `[3,4]` starts at 3 >= 3 ✓
  - `[1,2]`: `[2,3]` starts at 2 >= 2 ✓

**Constraints:**
- `1 <= intervals.length <= 2 * 10^4`
- `-10^6 <= start_i <= end_i <= 10^6`
- Each start point is unique

## Observations

1. **Key Insight**: For each interval's end point, we need to find the minimum start point that is >= that end. This is a classic "smallest element >= X" problem → **Binary Search**.

2. **Index Tracking**: Since we'll sort intervals by start points but need to return results in original order, we must preserve original indices.

3. **Sorted Starts**: If we extract and sort all start points, we can use binary search to find the smallest start >= each interval's end.

4. **Complexity Analysis**:
   - Time: O(n log n) for sorting + O(n log n) for n binary searches = **O(n log n)**
   - Space: O(n) for the combined list

5. **Edge Cases**:
   - Single interval (always returns -1)
   - Interval that is its own right interval
   - No right interval exists for any interval

## Solution

The solution uses **binary search on sorted start points**:

1. **Prepare Data**: Create a combined list `[start, end, original_index]` for each interval to preserve original positions after sorting.

2. **Sort by Start**: Sort all intervals by their start points. This allows binary search to work correctly.

3. **Binary Search per Interval**: For each interval:
   - Search for the smallest start point that is >= the current interval's end
   - Use binary search to find this in O(log n)
   - Store the original index of the found interval

4. **Detailed Algorithm**:
   ```
   For each interval i with end value:
     - Binary search in sorted starts for smallest start >= end
     - If found, record the original index
     - If not found, record -1
   ```

5. **Binary Search Logic**:
   - `left` and `right` pointers narrow down the search space
   - When `combined[mid][0] >= combined[i][1]`: this could be a candidate, save it and search left for smaller values
   - Otherwise: search right for larger values
   - `idx = n` means no valid start was found → return -1

**Time Complexity**: O(n log n) - sorting + n binary searches
**Space Complexity**: O(n) - combined array

# Tags
Binary Search, Sorting, Array

