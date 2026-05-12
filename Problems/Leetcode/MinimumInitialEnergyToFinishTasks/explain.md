## Problem

https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/

You are given an array `tasks` where `tasks[i] = [actuali, minimumi]`:
- `actuali` is the actual amount of energy you spend to finish the ith task.
- `minimumi` is the minimum amount of energy you require to begin the ith task.

For example, if the task is [10, 12] and your current energy is 11, you cannot start this task. However, if your current energy is 13, you can complete this task, and your energy will be 3 after finishing it.

You can finish the tasks in any order you like.

**Return the minimum initial amount of energy you will need to finish all the tasks.**

### Examples

**Example 1:**
```
Input: tasks = [[1,2],[2,4],[4,8]]
Output: 8
Explanation:
Starting with 8 energy, we finish the tasks in the following order:
- 3rd task. Now energy = 8 - 4 = 4.
- 2nd task. Now energy = 4 - 2 = 2.
- 1st task. Now energy = 2 - 1 = 1.
```

**Example 2:**
```
Input: tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]
Output: 32
```

**Example 3:**
```
Input: tasks = [[1,7],[2,8],[3,9],[4,10],[5,11],[6,12]]
Output: 27
```

### Constraints
- 1 ≤ tasks.length ≤ 10^5
- 1 ≤ actuali ≤ minimumi ≤ 10^4

## Observations

1. **Order Matters**: The order in which we complete tasks significantly affects the minimum initial energy needed. We cannot complete all tasks in arbitrary order.

2. **Greedy Sorting Strategy**: The key insight is to sort tasks by the **difference between minimum and actual energy** in **descending order** (`minimum - actual`).
   - Why? Tasks with larger differences (`minimum - actual`) represent tasks that "waste" more energy relative to their requirement. By doing these tasks first (in reverse order of execution), we minimize the initial energy needed.

3. **Working Backwards Logic**: Although we process tasks in the sorted order, the algorithm conceptually works backwards:
   - Start from the end of our task sequence and track what energy we need at each step.
   - To execute a task, we must have at least `minimum` energy before the task starts.
   - After executing the task, our energy decreases by `actual`.

4. **Energy Adjustment**: When processing a task in order:
   - If current energy < minimum requirement, we must add the deficit to our result (initial energy needed).
   - Then, we simulate completing the task by reducing current energy by `actual`.

5. **Why Reverse Sort Works**:
   - Consider two adjacent tasks in the sorted sequence: task A and task B.
   - If we do A before B, and A requires more energy buffer relative to its cost, placing high-difference tasks first (when energy is highest) prevents us from falling below minimum requirements for subsequent tasks.
   - By sorting in descending order of `minimum - actual`, we handle the "expensive" tasks first, leaving "cheaper" tasks for later.

## Solution

```python
class Solution:
    def minimumEffort(self, tasks: List[List[int]]) -> int:
        # Sort tasks by (minimum - actual) in descending order
        # This ensures we tackle high-difference tasks first
        tasks.sort(key=lambda x: x[1] - x[0], reverse=True)
        
        res = 0      # Minimum initial energy required
        cur = 0      # Current simulated energy at each step
        
        for actual, minimum in tasks:
            # If current energy is less than minimum requirement,
            # we need to increase our initial energy
            if cur < minimum:
                res += minimum - cur
                cur = minimum
            
            # Simulate completing the task
            # Energy decreases by actual amount
            cur -= actual
        
        return res
```

### Complexity Analysis

- **Time Complexity**: O(n log n) where n is the number of tasks
  - Dominated by the sorting operation
  - Single pass through tasks takes O(n)

- **Space Complexity**: O(1) or O(n) depending on sorting implementation
  - Excluding the space used by the sorting algorithm

### Algorithm Walkthrough (Example 1)

```
tasks = [[1,2],[2,4],[4,8]]
Sorted by (minimum - actual) descending: [[4,8],[2,4],[1,2]]
Differences: [8-4=4], [4-2=2], [2-1=1]

Step 1: Task [4, 8]
  cur = 0, minimum = 8
  cur < minimum, so res += 8 - 0 = 8, cur = 8
  cur -= 4, so cur = 4

Step 2: Task [2, 4]
  cur = 4, minimum = 4
  cur >= minimum (not taken)
  cur -= 2, so cur = 2

Step 3: Task [1, 2]
  cur = 2, minimum = 2
  cur >= minimum (not taken)
  cur -= 1, so cur = 1

Result: res = 8
```

### Key Insights

1. **Greedy is Optimal**: This greedy approach of sorting by `minimum - actual` difference guarantees the minimum initial energy. Proof relies on exchange argument: if any two adjacent tasks could be swapped to reduce required energy, our sort order would already prevent this.

2. **Backward Thinking**: We iterate forward through sorted tasks but conceptually work backwards from the final state, ensuring each intermediate state is feasible.

3. **Buffer Management**: The algorithm continuously manages the energy buffer needed—if we ever dip below a task's minimum, we adjust the initial energy accordingly.

# Tags

- Greedy Algorithm
- Sorting
- Energy/Resource Management

