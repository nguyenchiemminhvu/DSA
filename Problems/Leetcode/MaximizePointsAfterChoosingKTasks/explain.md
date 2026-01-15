## Problem

https://leetcode.com/problems/maximize-points-after-choosing-k-tasks/description/

```
You are given two integer arrays, technique1 and technique2, each of length n, where n represents 
the number of tasks to complete.

- If the ith task is completed using technique 1, you earn technique1[i] points.
- If it is completed using technique 2, you earn technique2[i] points.

You are also given an integer k, representing the minimum number of tasks that must be completed 
using technique 1.

You must complete at least k tasks using technique 1 (they do not need to be the first k tasks).
The remaining tasks may be completed using either technique.

Return an integer denoting the maximum total points you can earn.

Example 1:
Input: technique1 = [5,2,10], technique2 = [10,3,8], k = 2
Output: 22
Explanation: We must complete at least k = 2 tasks using technique1.
Choosing technique1[1] and technique1[2] (completed using technique 1), and technique2[0] 
(completed using technique 2), yields the maximum points: 2 + 10 + 10 = 22.

Example 2:
Input: technique1 = [10,20,30], technique2 = [5,15,25], k = 2
Output: 60
Explanation: We must complete at least k = 2 tasks using technique1.
Choosing all tasks using technique 1 yields the maximum points: 10 + 20 + 30 = 60.

Example 3:
Input: technique1 = [1,2,3], technique2 = [4,5,6], k = 0
Output: 15
Explanation: Since k = 0, we are not required to choose any task using technique1.
Choosing all tasks using technique 2 yields the maximum points: 4 + 5 + 6 = 15.

Constraints:
- 1 <= n == technique1.length == technique2.length <= 10^5
- 1 <= technique1[i], technique2[i] <= 10^5
- 0 <= k <= n
```

## Observations

1. **Constraint**: We must use technique1 for at least k tasks, meaning we can use technique2 for at most (n - k) tasks.

2. **Greedy Opportunity**: For each task, we can calculate the gain/loss if we choose technique2 instead of technique1:
   - Gain = `technique2[i] - technique1[i]`
   - Positive gain means technique2 is better
   - Negative gain means technique1 is better

3. **Strategy**: Start by assuming all tasks use technique1 (satisfies the constraint), then greedily switch to technique2 for tasks that provide the maximum gain.

4. **Max Heap Usage**: Use a max heap to efficiently get the tasks with the highest gain when switching from technique1 to technique2.

## Solution

### Approach: Greedy with Max Heap

**Algorithm**:
1. Initialize result as the sum of all technique1 values (assume all tasks use technique1)
2. For each task, calculate the gain: `technique2[i] - technique1[i]`
3. Store all gains in a max heap (use negative values for Python's min heap)
4. We can switch at most `(n - k)` tasks from technique1 to technique2
5. Greedily pop from the heap `(n - k)` times:
   - If the gain is positive, add it to the result
   - This effectively switches that task from technique1 to technique2

**Why it works**:
- Starting with all technique1 ensures we satisfy the "at least k tasks" constraint
- Switching at most (n - k) tasks ensures we maintain at least k tasks using technique1
- Greedily selecting switches with maximum gain gives the optimal result

```python
import heapq

class Solution:
    def maxPoints(self, tech1: List[int], tech2: List[int], k: int) -> int:
        n = len(tech1)
        
        # Start by assuming all tasks use technique1
        res = sum(tech1)
        
        # Calculate gains for switching from technique1 to technique2
        pq = []
        for i in range(n):
            heapq.heappush(pq, -(tech2[i] - tech1[i]))  # Max heap using negation
        
        # We can switch at most (n - k) tasks to technique2
        while k < n:
            val = heapq.heappop(pq)
            val *= -1  # Convert back to positive
            if val > 0:  # Only add positive gains
                res += val
            k += 1
        
        return res
```

**Complexity**:
- Time: O(n log n) - building heap and popping (n-k) elements
- Space: O(n) - for the heap

# Tags
`greedy` `heap` `priority-queue` `array`

