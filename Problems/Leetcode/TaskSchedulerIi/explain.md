## Problem

https://leetcode.com/problems/task-scheduler-ii/description/

```
You are given a 0-indexed array of positive integers tasks, representing tasks that need to be completed in order, 
where tasks[i] represents the type of the ith task.

You are also given a positive integer space, which represents the minimum number of days that must pass after 
the completion of a task before another task of the same type can be performed.

Each day, until all tasks have been completed, you must either:
- Complete the next task from tasks, or
- Take a break.

Return the minimum number of days needed to complete all tasks.

Example 1:
Input: tasks = [1,2,1,2,3,1], space = 3
Output: 9
Explanation:
One way to complete all tasks in 9 days is as follows:
Day 1: Complete the 0th task.
Day 2: Complete the 1st task.
Day 3: Take a break.
Day 4: Take a break.
Day 5: Complete the 2nd task.
Day 6: Complete the 3rd task.
Day 7: Take a break.
Day 8: Complete the 4th task.
Day 9: Complete the 5th task.
It can be shown that the tasks cannot be completed in less than 9 days.

Example 2:
Input: tasks = [5,8,8,5], space = 2
Output: 6
Explanation:
One way to complete all tasks in 6 days is as follows:
Day 1: Complete the 0th task.
Day 2: Complete the 1st task.
Day 3: Take a break.
Day 4: Take a break.
Day 5: Complete the 2nd task.
Day 6: Complete the 3rd task.
It can be shown that the tasks cannot be completed in less than 6 days.

Constraints:
- 1 <= tasks.length <= 10^5
- 1 <= tasks[i] <= 10^9
- 1 <= space <= tasks.length
```

## Observations

1. **Order matters**: Tasks must be completed in the given order - we cannot reorder tasks to optimize the schedule.

2. **Cooldown constraint**: After completing a task of type `t`, we must wait at least `space` days before we can complete another task of type `t`.

3. **Greedy approach**: Since we must complete tasks in order, we should complete each task as early as possible. If we can't complete the next task due to cooldown, we skip days.

4. **State tracking**: We need to track the last day each task type was completed to check if we've waited long enough.

5. **Key insight**: For each task, we either:
   - Complete it on the current day (if cooldown satisfied or first occurrence)
   - Wait until cooldown expires (if task type was recently completed)

## Solution

### Approach: Greedy with Hash Map

**Algorithm:**
1. Use a dictionary `prev_day` to track the last day each task type was completed
2. Iterate through tasks in order with `cur_day` starting at 1
3. For each task:
   - Check if this task type was completed before (exists in `prev_day`)
   - If yes, calculate the earliest day we can complete it: `prev_day[task] + space + 1`
   - If current day is before the earliest allowed day, jump to the earliest day
   - Mark this task as completed on `cur_day` and increment day counter
4. Return `cur_day - 1` (we increment one extra time after the last task)

**Implementation:**
```python
class Solution:
    def taskSchedulerII(self, tasks: List[int], space: int) -> int:
        prev_day = {}
        cur_day = 1
        for task in tasks:
            prev = float('-inf')
            if task in prev_day:
                prev = prev_day[task]
            if cur_day <= prev + space:
                cur_day = prev + space + 1
            
            prev_day[task] = cur_day
            cur_day += 1
        return cur_day - 1
```

**Example walkthrough (tasks = [1,2,1,2,3,1], space = 3):**
- Day 1: Complete task 1 (index 0), prev_day = {1: 1}
- Day 2: Complete task 2 (index 1), prev_day = {1: 1, 2: 2}
- Task 1 (index 2): Last completed on day 1, need to wait until day 1 + 3 + 1 = 5
- Day 5: Complete task 1 (index 2), prev_day = {1: 5, 2: 2}
- Task 2 (index 3): Last completed on day 2, need to wait until day 2 + 3 + 1 = 6
- Day 6: Complete task 2 (index 3), prev_day = {1: 5, 2: 6}
- Day 7: Complete task 3 (index 4), prev_day = {1: 5, 2: 6, 3: 7}
- Task 1 (index 5): Last completed on day 5, need to wait until day 5 + 3 + 1 = 9
- Day 9: Complete task 1 (index 5)
- Result: 9 days

**Time Complexity:** O(n) where n is the number of tasks - single pass through the array

**Space Complexity:** O(k) where k is the number of unique task types (at most n)

# Tags

