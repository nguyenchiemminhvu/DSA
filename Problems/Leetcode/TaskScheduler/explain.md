## Problem

https://leetcode.com/problems/task-scheduler/description/

```
You are given an array of CPU tasks, each labeled with a letter from A to Z, and a number n. 
Each CPU interval can be idle or allow the completion of one task. Tasks can be completed in 
any order, but there's a constraint: there has to be a gap of at least n intervals between 
two tasks with the same label.

Return the minimum number of CPU intervals required to complete all tasks.

Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.

Example 2:
Input: tasks = ["A","C","A","B","D","B"], n = 1
Output: 6
Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.

Example 3:
Input: tasks = ["A","A","A", "B","B","B"], n = 3
Output: 10
Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.

Constraints:
- 1 <= tasks.length <= 10^4
- tasks[i] is an uppercase English letter
- 0 <= n <= 100
```

## Observations

1. **Greedy Approach**: To minimize idle time, we should always execute the task with the highest remaining count when available.

2. **Cooldown Constraint**: After executing a task, it must wait at least `n` intervals before being executed again. This means if we execute task A at time `t`, it can't be executed again until time `t + n + 1`.

3. **Priority Queue**: A max heap helps us efficiently select the task with the highest frequency at each step.

4. **Cooldown Queue**: We need a separate queue to track tasks that are currently on cooldown along with the timestamp when they become available again.

5. **Time Simulation**: We simulate each time interval, moving tasks from cooldown back to the priority queue when they become available, and executing the highest priority task if one exists.

6. **Idle Time**: If no tasks are available (priority queue is empty but cooldown queue has tasks), the CPU must idle.

## Solution

```python
from typing import List
from collections import Counter, deque
import heapq

class Solution:
    def leastInterval(self, tasks: List[str], k: int) -> int:
        counter = Counter(tasks)
        pq = []
        for task, count in counter.items():
            heapq.heappush(pq, (-count, task))
        
        cooldown = deque() # time_available, task, count
        cur_time = 0
        while pq or cooldown:
            cur_time += 1

            while cooldown and cooldown[0][0] <= cur_time:
                timestamp, task, count = cooldown[0]
                heapq.heappush(pq, (-count, task))
                cooldown.popleft()

            if pq:
                neg_count, task = heapq.heappop(pq)
                count = -neg_count
                count -= 1
                if count > 0:
                    cooldown.append((cur_time + k + 1, task, count))
        
        return cur_time
```

### Algorithm Explanation

1. **Count Task Frequencies**: Use `Counter` to count how many times each task appears.

2. **Initialize Max Heap**: Push all tasks into a max heap (using negative counts since Python's heapq is a min heap). This allows us to always get the task with the highest remaining count in O(log n) time.

3. **Initialize Cooldown Queue**: Create a deque to store tasks that are on cooldown. Each entry is `(available_time, task, remaining_count)`.

4. **Time Simulation Loop**: While there are tasks to execute (either in the priority queue or cooldown):
   - Increment current time
   - **Check cooldown queue**: Move any tasks whose cooldown has expired back to the priority queue
   - **Execute task**: If the priority queue has tasks, pop the one with highest count, execute it (decrement count), and if it still has remaining executions, add it to cooldown with timestamp `current_time + k + 1`
   - **Implicit idle**: If pq is empty but cooldown has tasks, the CPU idles (we just increment time)

5. **Return Total Time**: The current time represents the minimum intervals needed.

### Complexity Analysis

- **Time Complexity**: O(N * M) where N is the number of intervals and M is the number of unique tasks. In the worst case, this is O(N log M) for heap operations over N intervals.
- **Space Complexity**: O(M) for storing unique tasks in the counter, heap, and cooldown queue.

### Key Insight

The greedy strategy of always executing the most frequent available task minimizes idle time because:
- High-frequency tasks are the bottleneck (they determine the minimum schedule length)
- By executing them as soon as possible, we interleave other tasks optimally
- This maximizes the utilization of the cooldown periods

# Tags
- Greedy
- Priority Queue (Heap)
- Queue
- Hash Table
- Counting
- Scheduling

