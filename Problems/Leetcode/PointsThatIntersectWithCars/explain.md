## Problem

https://leetcode.com/problems/points-that-intersect-with-cars/description/

```
You are given a 0-indexed 2D integer array nums representing the coordinates of the cars parking on a number line. For any index i, nums[i] = [starti, endi] where starti is the starting point of the ith car and endi is the ending point of the ith car.

Return the number of integer points on the line that are covered with any part of a car.

Example 1:

Input: nums = [[3,6],[1,5],[4,7]]
Output: 7
Explanation: All the points from 1 to 7 intersect at least one car, therefore the answer would be 7.

Example 2:

Input: nums = [[1,3],[5,8]]
Output: 7
Explanation: Points intersecting at least one car are 1, 2, 3, 5, 6, 7, 8. There are a total of 7 points, therefore the answer would be 7.

Constraints:

1 <= nums.length <= 100
nums[i].length == 2
1 <= starti <= endi <= 100
```

## Observations

1. **Range Coverage Problem**: We need to find how many integer points are covered by at least one car (interval).

2. **Constraints Analysis**: 
   - Maximum 100 cars
   - Each car position is between 1 and 100
   - This small constraint allows for efficient array-based solutions

3. **Overlapping Intervals**: Cars can overlap, and we only need to count each point once, regardless of how many cars cover it.

4. **Key Insight**: This is a classic "range increment" problem that can be solved efficiently using difference arrays (prefix sum technique).

## Solution

The solution uses a **difference array** approach with prefix sums:

### Algorithm Explanation:

1. **Initialize Difference Array**: Create an array `prefix` of size 111 (to handle indices 1-100 safely).

2. **Mark Range Increments**: For each car `[left, right]`:
   - Add 1 at position `left` (start of coverage)
   - Subtract 1 at position `right + 1` (end of coverage + 1)
   - This marks the "difference" where coverage starts and ends

3. **Build Prefix Sum**: Convert the difference array to actual coverage counts:
   - `prefix[i] += prefix[i-1]` accumulates the running count
   - After this step, `prefix[i]` represents how many cars cover point `i`

4. **Count Covered Points**: Count all positions where `prefix[i] > 0`

### Example Walkthrough:
For `nums = [[3,6],[1,5],[4,7]]`:

**Step 1**: Initialize difference array
```
prefix = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ...]
```

**Step 2**: Apply range increments
- Car [3,6]: `prefix[3] += 1`, `prefix[7] -= 1`
- Car [1,5]: `prefix[1] += 1`, `prefix[6] -= 1`  
- Car [4,7]: `prefix[4] += 1`, `prefix[8] -= 1`

```
prefix = [0, 1, 0, 1, 1, 0, -1, -1, -1, 0, 0, ...]
```

**Step 3**: Build prefix sum
```
prefix = [0, 1, 1, 2, 3, 3, 2, 1, 0, 0, 0, ...]
```

**Step 4**: Count positions > 0
Points 1,2,3,4,5,6,7 are covered → Answer = 7

### Complexity:
- **Time**: O(n + k) where n = number of cars, k = range size (100)
- **Space**: O(k) for the difference array

### Why This Works:
- The difference array technique efficiently handles overlapping ranges
- Prefix sum converts "range updates" to "point queries"
- Much more efficient than naive approaches like marking each point individually

# Tags

Array, Prefix Sum, Difference Array, Range Processing

