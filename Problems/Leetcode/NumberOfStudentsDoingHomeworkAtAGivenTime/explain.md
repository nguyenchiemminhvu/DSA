## Problem

https://leetcode.com/problems/number-of-students-doing-homework-at-a-given-time/description/

```
Given two integer arrays startTime and endTime and given an integer queryTime.

The ith student started doing their homework at the time startTime[i] and finished it at time endTime[i].

Return the number of students doing their homework at time queryTime. More formally, return the number of students where queryTime lays in the interval [startTime[i], endTime[i]] inclusive.

Example 1:

Input: startTime = [1,2,3], endTime = [3,2,7], queryTime = 4
Output: 1
Explanation: We have 3 students where:
The first student started doing homework at time 1 and finished at time 3 and wasn't doing anything at time 4.
The second student started doing homework at time 2 and finished at time 2 and also wasn't doing anything at time 4.
The third student started doing homework at time 3 and finished at time 7 and was the only student doing homework at time 4.

Example 2:

Input: startTime = [4], endTime = [4], queryTime = 4
Output: 1
Explanation: The only student was doing their homework at the queryTime.

Constraints:

startTime.length == endTime.length
1 <= startTime.length <= 100
1 <= startTime[i] <= endTime[i] <= 1000
1 <= queryTime <= 1000
```

## Observations

1. **Problem Type**: This is a straightforward interval overlap problem where we need to check if a query point falls within given intervals.

2. **Input Analysis**:
   - Two arrays `startTime` and `endTime` of equal length representing homework intervals for each student
   - A query time `q` to check how many students are doing homework at that moment
   - Each student `i` does homework from `startTime[i]` to `endTime[i]` (inclusive)

3. **Key Insight**: A student is doing homework at time `q` if and only if `startTime[i] <= q <= endTime[i]`

4. **Constraints Analysis**:
   - Small input size (≤ 100 students) makes brute force approach acceptable
   - Time values are bounded (≤ 1000), so no overflow concerns
   - Each student's start time ≤ end time is guaranteed

## Solution

1. **Initialize Counter**: Start with `count = 0` to track students doing homework at query time
2. **Iterate Through Students**: For each student `i` from 0 to n-1:
   - Check if the query time `q` falls within the student's homework interval `[s[i], e[i]]`
   - This requires: `s[i] <= q <= e[i]` (both bounds inclusive)
3. **Count Valid Students**: Increment counter for each student whose interval contains the query time
4. **Return Result**: The final count represents the number of busy students

**Time Complexity**: O(n) where n is the number of students
- Single pass through all students

**Space Complexity**: O(1)
- Only using a constant amount of extra space for the counter

**Example Walkthrough**:
- Input: `startTime = [1,2,3]`, `endTime = [3,2,7]`, `queryTime = 4`
- Student 0: interval [1,3] → 4 ∉ [1,3] → not counting
- Student 1: interval [2,2] → 4 ∉ [2,2] → not counting  
- Student 2: interval [3,7] → 4 ∈ [3,7] → count++
- Result: 1 student doing homework at time 4

**Alternative Approaches**:
- For larger datasets, we could use interval trees or segment trees, but the linear approach is optimal here given the constraints

# Tags

`Array` `Simulation` `Interval` `Easy` `Linear Scan`

