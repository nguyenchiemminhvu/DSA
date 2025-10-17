## Problem

https://leetcode.com/problems/gas-station/description/

```
There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique.

Example 1:

Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.

Example 2:

Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.

Constraints:

n == gas.length == cost.length
1 <= n <= 105
0 <= gas[i], cost[i] <= 104
The input is generated such that the answer is unique.
```

## Observations

1. **Total Gas vs Total Cost Check**: If the total gas available across all stations is less than the total cost required to complete the entire circuit, it's impossible to complete the journey regardless of the starting point.

2. **Greedy Approach**: We can use a greedy approach to find the optimal starting point. If we can't reach a station from our current starting point, any station between our current start and that unreachable station also cannot be a valid starting point.

3. **Net Gain/Loss**: At each station, we calculate the net gain/loss as `gas[i] - cost[i]`. If this is positive, we gain fuel; if negative, we lose fuel.

4. **Reset Strategy**: When our current tank goes negative (meaning we can't reach the next station), we reset and try starting from the next station. This is based on the key insight that if we can't reach station `j` from station `i`, then no station between `i` and `j-1` can be a valid starting point either.

5. **Uniqueness Guarantee**: The problem states that if a solution exists, it's guaranteed to be unique, which simplifies our approach.

## Solution

1. **Initial Check**: First verify if `sum(gas) >= sum(cost)`. If not, return -1 immediately.

2. **Single Pass**: Iterate through all stations once, maintaining:
   - `cur_tank`: Fuel level starting from current candidate station
   - `selected`: Index of current candidate starting station

3. **Greedy Selection**: When `cur_tank` becomes negative at station `i`:
   - We know stations `selected` through `i` cannot be valid starting points
   - Reset and try starting from station `i+1`

4. **Why This Works**: 
   - If we fail to reach station `j` starting from station `i`, then starting from any station between `i` and `j-1` will also fail
   - This is because those intermediate stations would have even less fuel accumulated when reaching the failure point

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space

**Key Insight**: The greedy approach works because of the circular nature and the guarantee of solution uniqueness. Once we find a starting point where we can complete the journey without our tank going negative, that must be the answer.

## Tags

array, greedy