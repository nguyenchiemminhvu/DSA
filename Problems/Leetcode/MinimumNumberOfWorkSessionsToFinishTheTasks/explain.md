## Problem

https://leetcode.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/description/

```
There are n tasks assigned to you. The task times are represented as an integer array tasks of length n, 
where the ith task takes tasks[i] hours to finish. A work session is when you work for at most sessionTime 
consecutive hours and then take a break.

You should finish the given tasks in a way that satisfies the following conditions:
- If you start a task in a work session, you must complete it in the same work session.
- You can start a new task immediately after finishing the previous one.
- You may complete the tasks in any order.

Given tasks and sessionTime, return the minimum number of work sessions needed to finish all the tasks 
following the conditions above.

The tests are generated such that sessionTime is greater than or equal to the maximum element in tasks[i].

Example 1:
Input: tasks = [1,2,3], sessionTime = 3
Output: 2
Explanation: You can finish the tasks in two work sessions.
- First work session: finish the first and the second tasks in 1 + 2 = 3 hours.
- Second work session: finish the third task in 3 hours.

Example 2:
Input: tasks = [3,1,3,1,1], sessionTime = 8
Output: 2
Explanation: You can finish the tasks in two work sessions.
- First work session: finish all the tasks except the last one in 3 + 1 + 3 + 1 = 8 hours.
- Second work session: finish the last task in 1 hour.

Example 3:
Input: tasks = [1,2,3,4,5], sessionTime = 15
Output: 1
Explanation: You can finish all the tasks in one work session.

Constraints:
n == tasks.length
1 <= n <= 14
1 <= tasks[i] <= 10
max(tasks[i]) <= sessionTime <= 15
```

## Observations

1. **Small Input Size**: With n ≤ 14, we can use backtracking/DFS approaches that would be too slow for larger inputs.

2. **Bin Packing Problem**: This is a variant of the bin packing problem where we want to minimize the number of bins (sessions) needed to pack items (tasks) with a capacity constraint (sessionTime).

3. **Greedy Heuristic**: Sorting tasks in descending order helps place larger tasks first, making it easier to fill remaining space with smaller tasks - this often leads to better packing.

4. **State Space**: We need to track:
   - Which task we're currently trying to place (index i)
   - The current sessions and their remaining capacity
   - Which tasks have been assigned

5. **Pruning Opportunity**: If the current number of sessions already equals or exceeds the best result found so far, we can prune this branch.

6. **Two Choices per Task**: For each task, we can either:
   - Add it to an existing session (if it fits)
   - Create a new session for it

## Solution

### Approach: Backtracking with Pruning

The solution uses DFS (depth-first search) with backtracking to explore all possible ways to assign tasks to sessions.

**Key Components:**

1. **Sorting**: Tasks are sorted in descending order to try placing larger tasks first (greedy heuristic for better pruning).

2. **State Tracking**:
   - `tmp`: List storing the current time used in each active session
   - `used`: Set tracking which tasks have been assigned (used for backtracking)
   - `res`: Array (used as reference) to store the minimum number of sessions found

3. **DFS Function**:
   - **Base Case (Pruning)**: If current sessions ≥ best result, stop exploring this branch
   - **Base Case (Success)**: If all tasks assigned (i ≥ n), update the result
   - **Try Existing Sessions**: Attempt to add task i to any existing session if it doesn't exceed the limit
   - **Create New Session**: Try creating a new session for task i

4. **Backtracking**: After trying each possibility, undo the changes (remove from used set, restore session time) to explore other branches.

**Time Complexity**: O(n! * 2^n) in the worst case, but with heavy pruning in practice. For n ≤ 14, this is acceptable.

**Space Complexity**: O(n) for the recursion stack and tracking structures.

```python
class Solution:
    def minSessions(self, tasks: List[int], limit: int) -> int:
        n = len(tasks)
        tasks.sort(reverse=True)  # Sort descending for better pruning
        res = [n]  # Worst case: each task in its own session
        used = set()  # Track which tasks are assigned
        tmp = []  # Current sessions with their used time
        
        def dfs(i: int) -> None:
            # Prune: if current sessions >= best result, stop
            if len(tmp) >= res[0]:
                return
            
            # All tasks assigned, update result
            if i >= n:
                res[0] = min(res[0], len(tmp))
                return
            
            # Try adding task i to any existing session
            for j in range(len(tmp)):
                if i not in used:
                    if tmp[j] + tasks[i] <= limit:
                        tmp[j] += tasks[i]
                        used.add(i)
                        dfs(i + 1)
                        used.remove(i)  # Backtrack
                        tmp[j] -= tasks[i]
            
            # Try creating a new session for task i
            if i not in used:
                tmp.append(tasks[i])
                used.add(i)
                dfs(i + 1)
                used.remove(i)  # Backtrack
                tmp.pop()
        
        dfs(0)
        return res[0]
```

**Example Walkthrough** (tasks = [1,2,3], sessionTime = 3):

After sorting: [3,2,1]

1. Task 3 (3 hours): Create session 1 → sessions = [3]
2. Task 2 (2 hours): Can't fit in session 1 (3+2 > 3), create session 2 → sessions = [3, 2]
3. Task 1 (1 hour): Can fit in session 2 (2+1 = 3) → sessions = [3, 3]
4. Result: 2 sessions

# Tags

`Dynamic Programming`, `Backtracking`, `Bit Manipulation`, `Bitmask`, `DFS`, `Bin Packing`

