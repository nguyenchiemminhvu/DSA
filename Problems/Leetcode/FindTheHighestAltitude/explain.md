## Problem

https://leetcode.com/problems/find-the-highest-altitude/description/

```
There is a biker going on a road trip. The road trip consists of n + 1 points at different altitudes. The biker starts his trip on point 0 with altitude equal 0.

You are given an integer array gain of length n where gain[i] is the net gain in altitude between points i​​​​​​ and i + 1 for all (0 <= i < n). Return the highest altitude of a point.

Example 1:

Input: gain = [-5,1,5,0,-7]
Output: 1
Explanation: The altitudes are [0,-5,-4,1,1,-6]. The highest is 1.

Example 2:

Input: gain = [-4,-3,-2,-1,4,3,2]
Output: 0
Explanation: The altitudes are [0,-4,-7,-9,-10,-6,-3,-1]. The highest is 0.

Constraints:

n == gain.length
1 <= n <= 100
-100 <= gain[i] <= 100
```

## Observations

1. **Starting Point**: The biker starts at altitude 0 (point 0).

2. **Gain Array Interpretation**: 
   - `gain[i]` represents the net altitude change from point `i` to point `i+1`
   - If `gain = [-5,1,5,0,-7]`, the actual altitudes at each point are:
     - Point 0: 0 (starting altitude)
     - Point 1: 0 + (-5) = -5
     - Point 2: -5 + 1 = -4
     - Point 3: -4 + 5 = 1
     - Point 4: 1 + 0 = 1
     - Point 5: 1 + (-7) = -6

3. **Key Insight**: We need to track the running sum (cumulative altitude) and keep track of the maximum altitude encountered.

4. **Edge Cases**:
   - The starting altitude (0) should be considered as a candidate for the highest altitude
   - All gains could be negative, making 0 the highest altitude
   - The highest altitude might occur at any point along the journey, not necessarily at the end

5. **Algorithm Complexity**: 
   - Time: O(n) - single pass through the gain array
   - Space: O(1) - only using two variables to track current and maximum altitude

## Solution

**Step-by-step walkthrough** with `gain = [-5,1,5,0,-7]`:

1. **Initialization**: `res = 0`, `cur = 0`
2. **Point 0 → Point 1**: `cur = 0 + (-5) = -5`, `res = max(0, -5) = 0`
3. **Point 1 → Point 2**: `cur = -5 + 1 = -4`, `res = max(0, -4) = 0`
4. **Point 2 → Point 3**: `cur = -4 + 5 = 1`, `res = max(0, 1) = 1`
5. **Point 3 → Point 4**: `cur = 1 + 0 = 1`, `res = max(1, 1) = 1`
6. **Point 4 → Point 5**: `cur = 1 + (-7) = -6`, `res = max(1, -6) = 1`

**Return**: `1`

**Why this works**:
- We simulate the biker's journey by maintaining a running sum of gains
- At each step, we check if the current altitude is the highest we've seen
- The initial altitude of 0 is implicitly considered since `res` starts at 0

# Tags

`Array` `Prefix Sum` `Simulation` `Easy`

