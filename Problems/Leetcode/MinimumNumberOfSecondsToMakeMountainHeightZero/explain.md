## Problem

https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/description/

```
You are given an integer mountainHeight denoting the height of a mountain.

You are also given an integer array workerTimes representing the work time of workers in seconds.

The workers work simultaneously to reduce the height of the mountain. For worker i:

To decrease the mountain's height by x, it takes workerTimes[i] + workerTimes[i] * 2 + ... + workerTimes[i] * x seconds. For example:
- To reduce the height of the mountain by 1, it takes workerTimes[i] seconds.
- To reduce the height of the mountain by 2, it takes workerTimes[i] + workerTimes[i] * 2 seconds, and so on.

Return an integer representing the minimum number of seconds required for the workers to make the height of the mountain 0.

Example 1:
Input: mountainHeight = 4, workerTimes = [2,1,1]
Output: 3
Explanation:
- Worker 0 reduces height by 1, taking 2 seconds.
- Worker 1 reduces height by 2, taking 1 + 1*2 = 3 seconds.
- Worker 2 reduces height by 1, taking 1 second.
- Since they work simultaneously, minimum time = max(2, 3, 1) = 3 seconds.

Example 2:
Input: mountainHeight = 10, workerTimes = [3,2,2,4]
Output: 12

Example 3:
Input: mountainHeight = 5, workerTimes = [1]
Output: 15
Explanation: Single worker takes 1 + 2 + 3 + 4 + 5 = 15 seconds.

Constraints:
- 1 <= mountainHeight <= 10^5
- 1 <= workerTimes.length <= 10^4
- 1 <= workerTimes[i] <= 10^6
```

## Observations

1. **Work Cost Pattern**: For a worker with base time `t`, reducing height by `x` units costs:
   - Cost = t * (1 + 2 + 3 + ... + x) = t * x * (x+1) / 2
   - This is an arithmetic series that grows quadratically

2. **Parallel Work**: All workers work simultaneously, so the total time is the maximum time any single worker takes

3. **Greedy Assignment**: To minimize the maximum time:
   - We should assign each unit of height reduction to the worker who can complete their NEXT unit fastest
   - This suggests using a min-heap to track which worker should work next

4. **Incremental Cost**: When a worker completes their k-th unit:
   - Their next (k+1)-th unit will cost: t * (k+1)
   - Their cumulative time becomes: t * k * (k+1) / 2

## Solution

**Approach: Greedy with Min-Heap**

The key insight is to simulate the process greedily:
- Always assign the next unit of work to the worker who will finish their next unit earliest
- Track each worker's state: (cumulative_time, base_time, next_multiplier)

**Algorithm:**
1. Initialize a min-heap with all workers, each starting at (base_time, base_time, 1)
   - The first element represents when this worker will finish their next task
   
2. For each unit of height (repeat `mountainHeight` times):
   - Pop the worker with minimum completion time from heap
   - Update the total time to the maximum seen so far
   - Calculate when this worker will finish their NEXT unit
   - Push the updated worker back to heap
   
3. Return the maximum time tracked

**Time Complexity**: O(H * log W) where H = mountainHeight, W = number of workers
- We perform H heap operations, each taking O(log W)

**Space Complexity**: O(W) for the heap

```python
import heapq

class Solution:
    def minNumberOfSeconds(self, height: int, times: List[int]) -> int:
        n = len(times)
        # (current_cumulative_time, base_time, next_multiplier)
        pq = [(t, t, 1) for t in times]
        heapq.heapify(pq)

        total_time_cost = 0
        while height > 0:
            cur_time_cost, init_time, multiplier = heapq.heappop(pq)
            # This worker finishes at cur_time_cost
            total_time_cost = max(total_time_cost, cur_time_cost)
            
            # Calculate cumulative time after completing next unit
            multiplier += 1
            cur_time_cost += init_time * multiplier
            
            heapq.heappush(pq, (cur_time_cost, init_time, multiplier))
            height -= 1
        
        return total_time_cost
```

**Example Walkthrough (mountainHeight=4, workerTimes=[2,1,1]):**

Initial heap: [(1,1,1), (1,1,1), (2,2,1)]

Step 1: Pop (1,1,1) → time=1, push (1+1*2=3,1,2) → height=3
Step 2: Pop (1,1,1) → time=1, push (1+1*2=3,1,2) → height=2  
Step 3: Pop (2,2,1) → time=2, push (2+2*2=6,2,2) → height=1
Step 4: Pop (3,1,2) → time=3, push (3+1*3=6,1,3) → height=0

Result: max(1,1,2,3) = 3 seconds

# Tags
- Greedy
- Heap/Priority Queue
- Simulation
- Math (Arithmetic Series)

