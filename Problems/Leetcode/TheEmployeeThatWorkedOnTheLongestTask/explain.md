## Problem

https://leetcode.com/problems/the-employee-that-worked-on-the-longest-task/description/

There are `n` employees, each with a unique id from `0` to `n - 1`.

You are given a 2D integer array `logs` where `logs[i] = [idi, leaveTimei]` where:
- `idi` is the id of the employee that worked on the ith task, and
- `leaveTimei` is the time at which the employee finished the ith task. All the values `leaveTimei` are unique.

**Note**: The ith task starts the moment right after the (i - 1)th task ends, and the 0th task starts at time 0.

Return the id of the employee that worked the task with the longest time. If there is a tie between two or more employees, return the smallest id among them.

**Constraints:**
- `2 <= n <= 500`
- `1 <= logs.length <= 500`
- `logs[i].length == 2`
- `0 <= idi <= n - 1`
- `1 <= leaveTimei <= 500`
- `idi != idi+1`
- `leaveTimei` are sorted in a strictly increasing order.

**Example 1:**
```
Input: n = 10, logs = [[0,3],[2,5],[0,9],[1,15]]
Output: 1
Explanation: 
Task 0: 0 to 3 = 3 units (employee 0)
Task 1: 3 to 5 = 2 units (employee 2)
Task 2: 5 to 9 = 4 units (employee 0)
Task 3: 9 to 15 = 6 units (employee 1) ← longest
```

**Example 2:**
```
Input: n = 26, logs = [[1,1],[3,7],[2,12],[7,17]]
Output: 3
Explanation: 
Task 0: 0 to 1 = 1 unit (employee 1)
Task 1: 1 to 7 = 6 units (employee 3) ← longest
Task 2: 7 to 12 = 5 units (employee 2)
Task 3: 12 to 17 = 5 units (employee 7)
```

**Example 3:**
```
Input: n = 2, logs = [[0,10],[1,20]]
Output: 0
Explanation: Both tasks take 10 units, return smallest id (0)
```

## Observations

1. **Task Duration Calculation**: Each task's duration is `current_leave_time - previous_leave_time`. The first task starts at time 0.

2. **Tracking Maximum**: We need to track which employee worked on the longest single task (not total time across all tasks).

3. **Tie Breaking**: When multiple employees have tasks with the same maximum duration, we must return the smallest employee id.

4. **Sequential Processing**: Since tasks are sequential and leave times are sorted, we can process logs in order, calculating each task duration on-the-fly.

5. **Key Insight**: We don't need to store all durations for each employee. We only need to track:
   - The current maximum task duration seen
   - The employee id associated with that maximum
   - Update when we find a longer duration or a tie with smaller id

## Solution

### Approach: Single Pass with Tracking

**Algorithm:**
1. Initialize tracking variables:
   - `max_time`: longest task duration seen so far
   - `res`: employee id with the longest task
   - `prev_time`: end time of previous task (starts at 0)

2. Iterate through each log entry:
   - Calculate current task duration: `timestamp - prev_time`
   - If this duration is greater than `max_time`:
     - Update `max_time` and `res`
   - If this duration equals `max_time`:
     - Update `res` to minimum of current `res` and current employee id (tie-breaking)
   - Update `prev_time` for next iteration

3. Return `res`

**Time Complexity:** O(m) where m is the length of logs
- Single pass through all log entries

**Space Complexity:** O(1)
- Only using constant extra space for tracking variables

**Note on the Provided Code:**
The given solution uses a `defaultdict` to track maximum duration per employee, but this is unnecessary overhead. We only need to track the global maximum and associated employee id, not per-employee maximums. A simpler version would be:

```python
class Solution:
    def hardestWorker(self, n: int, logs: List[List[int]]) -> int:
        res = -1
        prev_time = 0
        max_time = 0
        
        for emp, timestamp in logs:
            duration = timestamp - prev_time
            
            if duration > max_time:
                max_time = duration
                res = emp
            elif duration == max_time:
                res = min(res, emp)
            
            prev_time = timestamp
        
        return res
```

# Tags
`array` `simulation` `tracking` `greedy`

