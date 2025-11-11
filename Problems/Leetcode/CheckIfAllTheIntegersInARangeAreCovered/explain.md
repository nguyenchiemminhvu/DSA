## Problem

https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/description/

```
You are given a 2D integer array ranges and two integers left and right. Each ranges[i] = [starti, endi] represents an inclusive interval between starti and endi.

Return true if each integer in the inclusive range [left, right] is covered by at least one interval in ranges. Return false otherwise.

An integer x is covered by an interval ranges[i] = [starti, endi] if starti <= x <= endi.

Example 1:

Input: ranges = [[1,2],[3,4],[5,6]], left = 2, right = 5
Output: true
Explanation: Every integer between 2 and 5 is covered:
- 2 is covered by the first range.
- 3 and 4 are covered by the second range.
- 5 is covered by the third range.

Example 2:

Input: ranges = [[1,10],[10,20]], left = 21, right = 21
Output: false
Explanation: 21 is not covered by any range.

Constraints:

1 <= ranges.length <= 50
1 <= starti <= endi <= 50
1 <= left <= right <= 50
```

## Observations

1. **Problem Understanding**: We need to check if every integer in the range [left, right] is covered by at least one interval from the given ranges.

2. **Constraint Analysis**: 
   - All values are between 1 and 50, which is a small range
   - Maximum 50 ranges to process
   - This suggests we can use a simple array-based approach

3. **Key Insight**: Instead of checking each number individually, we can use a **difference array (prefix sum)** technique to efficiently track coverage.

4. **Coverage Tracking**: For each range [l, r], we increment coverage at position `l` and decrement at position `r+1`. This creates a "difference array" that when processed with prefix sums, gives us the actual coverage count at each position.

## Solution

1. **Initialize difference array**: Create an array of size 100 (covers all possible values 1-50 with buffer).

2. **Mark range boundaries**: For each range [l, r]:
   - Add +1 at position `l` (start of coverage)
   - Add -1 at position `r+1` (end of coverage, exclusive)

3. **Convert to actual coverage counts**: Use prefix sum to convert the difference array to actual coverage counts:
   - `prefix[i] += prefix[i-1]` accumulates the differences
   - After this step, `prefix[i]` represents how many ranges cover position `i`

4. **Check target range**: For each position in [left, right]:
   - If `prefix[i] <= 0`, it means no ranges cover this position
   - Return false immediately if any position is uncovered

**Example walkthrough** with `ranges = [[1,2],[3,4],[5,6]]`, `left = 2`, `right = 5`:

1. After marking boundaries:
   ```
   Index: 1  2  3  4  5  6  7
   Diff:  1  0 -1  1  0 -1  1 -1
   ```

2. After prefix sum:
   ```
   Index: 1  2  3  4  5  6  7
   Count: 1  1  0  1  1  0  1
   ```

3. Check range [2,5]: positions 2,3,4,5 have counts [1,0,1,1]
   - Position 3 has count 0, but wait... let me recalculate:

Actually, let me trace this more carefully:
- Range [1,2]: diff[1]+=1, diff[3]-=1
- Range [3,4]: diff[3]+=1, diff[5]-=1  
- Range [5,6]: diff[5]+=1, diff[7]-=1

After prefix sum: [0,1,1,1,1,1,1,0,...]
Positions 2,3,4,5 all have count ≥ 1, so return true.

**Time Complexity**: O(n + k) where n is the number of ranges and k is the range size (constant 100)
**Space Complexity**: O(k) for the difference array

# Tags

- Array
- Prefix Sum
- Difference Array
- Range Coverage

