## Problem

https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-i/description/

```
You are given two categories of theme park attractions: land rides and water rides.

Land rides:
- landStartTime[i] – the earliest time the ith land ride can be boarded.
- landDuration[i] – how long the ith land ride lasts.

Water rides:
- waterStartTime[j] – the earliest time the jth water ride can be boarded.
- waterDuration[j] – how long the jth water ride lasts.

A tourist must experience exactly one ride from each category, in either order.

Rules:
- A ride may be started at its opening time or any later moment.
- If a ride is started at time t, it finishes at time t + duration.
- Immediately after finishing one ride, the tourist may board the other (if it is already open) or wait until it opens.

Return the earliest possible time at which the tourist can finish both rides.

Example 1:
Input: landStartTime = [2,8], landDuration = [4,1], waterStartTime = [6], waterDuration = [3]
Output: 9

Example 2:
Input: landStartTime = [5], landDuration = [3], waterStartTime = [1], waterDuration = [10]
Output: 14

Constraints:
- 1 <= n, m <= 100
- landStartTime.length == landDuration.length == n
- waterStartTime.length == waterDuration.length == m
- 1 <= landStartTime[i], landDuration[i], waterStartTime[j], waterDuration[j] <= 1000
```

## Observations

1. **Brute Force Approach**: Since constraints are small (n, m ≤ 100), we can try all possible combinations of land and water rides.

2. **Two Orderings**: For each pair of rides (one land, one water), we can:
   - Take the land ride first, then the water ride
   - Take the water ride first, then the land ride
   
3. **Key Insight**: The order matters based on which ride opens earlier. We should sort the two selected rides by their start times to determine the optimal order.

4. **Scheduling Logic**: 
   - Start the first ride (earliest opening) at its start time
   - After finishing the first ride, check if the second ride is already open:
     - If yes: start immediately (at `first_end_time`)
     - If no: wait until it opens (at `second_start_time`)

5. **Time Complexity**: O(n × m) where n = number of land rides, m = number of water rides

## Solution

1. **Enumerate all pairs**: Try every combination of (land ride i, water ride j)

2. **Determine optimal order**: Sort the two selected rides by start time
   - The ride that opens earlier should be taken first

3. **Calculate finish time**:
   - First ride ends at: `first_start + first_duration`
   - Second ride starts at: `max(first_end, second_start)`
   - Total finish time: `start_time_of_second + second_duration`

4. **Two scenarios**:
   - **Case 1**: `first_end ≤ second_start` → Second ride hasn't opened, finish at `second_start + second_duration`
   - **Case 2**: `first_end > second_start` → Second ride already open, finish at `first_end + second_duration`

5. **Return minimum**: Track and return the earliest finish time across all combinations

**Time Complexity**: O(n × m) - try all pairs  
**Space Complexity**: O(1) - only use constant extra space

# Tags
#brute-force #simulation #scheduling #greedy #array #iteration

