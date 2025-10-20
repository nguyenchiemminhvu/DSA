## Problem

https://leetcode.com/problems/minimum-processing-time/

```
You have a certain number of processors, each having 4 cores. The number of tasks to be executed is four times the number of processors. Each task must be assigned to a unique core, and each core can only be used once.

You are given an array processorTime representing the time each processor becomes available and an array tasks representing how long each task takes to complete. Return the minimum time needed to complete all tasks.

Example 1:

Input: processorTime = [8,10], tasks = [2,2,3,1,8,7,4,5]

Output: 16

Explanation:

Assign the tasks at indices 4, 5, 6, 7 to the first processor which becomes available at time = 8, and the tasks at indices 0, 1, 2, 3 to the second processor which becomes available at time = 10. 

The time taken by the first processor to finish the execution of all tasks is max(8 + 8, 8 + 7, 8 + 4, 8 + 5) = 16.

The time taken by the second processor to finish the execution of all tasks is max(10 + 2, 10 + 2, 10 + 3, 10 + 1) = 13.

Example 2:

Input: processorTime = [10,20], tasks = [2,3,1,2,5,8,4,3]

Output: 23

Explanation:

Assign the tasks at indices 1, 4, 5, 6 to the first processor and the others to the second processor.

The time taken by the first processor to finish the execution of all tasks is max(10 + 3, 10 + 5, 10 + 8, 10 + 4) = 18.

The time taken by the second processor to finish the execution of all tasks is max(20 + 2, 20 + 1, 20 + 2, 20 + 3) = 23.

Constraints:

1 <= n == processorTime.length <= 25000
1 <= tasks.length <= 105
0 <= processorTime[i] <= 109
1 <= tasks[i] <= 109
tasks.length == 4 * n
```

## Observations

1. **Key Insight**: Each processor has 4 cores and can handle 4 tasks simultaneously. The completion time for a processor is determined by its start time plus the longest task assigned to it.

2. **Optimal Assignment Strategy**: To minimize the overall completion time, we should:
   - Assign the longest tasks to processors that become available earliest
   - This balances the load and prevents any single processor from becoming a bottleneck

3. **Greedy Approach**: 
   - Sort processors by availability time (ascending)
   - Sort tasks by duration (descending) 
   - Assign the 4 longest remaining tasks to the earliest available processor

4. **Why this works**: If we assign shorter tasks to earlier processors, those processors might finish early but the later processors with longer tasks will determine the overall completion time.

## Solution

1. **Sort cpu_time in ascending order**: We want to assign tasks to processors that become available earliest first.

2. **Sort tasks in descending order**: We want to assign the heaviest tasks to the earliest available processors.

3. **Greedy Assignment**: For each processor (starting with the earliest available):
   - Assign the next 4 longest tasks to it
   - The processor's completion time is `start_time + longest_task_duration`
   - Since tasks are sorted in descending order, `tasks[it]` is the longest among the 4 tasks assigned

4. **Track Maximum**: The overall completion time is the maximum completion time among all processors.

**Time Complexity**: O(n log n + m log m) where n = number of processors, m = number of tasks
**Space Complexity**: O(1) excluding input arrays

## Tags

array, greedy, sorting