## Problem

https://leetcode.com/problems/single-threaded-cpu/description/

You are given `n` tasks labeled from `0` to `n - 1` represented by a 2D integer array `tasks`, where `tasks[i] = [enqueueTimei, processingTimei]` means that the `i`th task will be available to process at `enqueueTimei` and will take `processingTimei` to finish processing.

You have a single-threaded CPU that can process at most one task at a time and will act in the following way:

- If the CPU is idle and there are no available tasks to process, the CPU remains idle.
- If the CPU is idle and there are available tasks, the CPU will choose the one with the **shortest processing time**. If multiple tasks have the same shortest processing time, it will choose the task with the **smallest index**.
- Once a task is started, the CPU will process the entire task without stopping.
- The CPU can finish a task then start a new one instantly.

Return the order in which the CPU will process the tasks.

**Example 1:**
```
Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]
Explanation: 
- At time = 1, task 0 is available and CPU starts processing it
- At time = 3, CPU finishes task 0 and starts task 2 (shortest among {1, 2})
- At time = 5, CPU finishes task 2 and starts task 3 (shortest among {1, 3})
- At time = 6, CPU finishes task 3 and starts task 1
```

**Example 2:**
```
Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
Output: [4,3,2,0,1]
Explanation: All tasks become available at time 7, CPU processes them in order of processing time (shortest first).
```

**Constraints:**
- `tasks.length == n`
- `1 <= n <= 10^5`
- `1 <= enqueueTimei, processingTimei <= 10^9`

## Observations

1. **Simulation Problem**: We need to simulate CPU task scheduling based on specific rules
2. **Two-tier Priority**: 
   - Primary: shortest processing time
   - Tiebreaker: smallest index
3. **Time Management**: CPU can be idle if no tasks are available, then jump to next task's enqueue time
4. **Order Matters**: We must preserve original task indices even after sorting

## Solution

### Approach: Priority Queue (Min Heap) + Time Simulation

**Key Idea**: Use a min heap to efficiently select the next task based on processing time and index, while simulating time progression.

**Algorithm Steps:**

1. **Preprocessing**:
   - Augment each task with its original index: `(enqueueTime, processingTime, originalIndex)`
   - Sort tasks by enqueue time to process them chronologically

2. **Simulation Loop**:
   - Maintain `cur_time` to track current CPU time
   - Use a min heap `pq` storing `(processingTime, originalIndex)` for available tasks
   
3. **Time Jump**: 
   - If heap is empty and CPU is idle, jump `cur_time` to the next task's enqueue time
   
4. **Enqueue Available Tasks**:
   - Add all tasks with `enqueueTime <= cur_time` to the heap
   - The heap automatically maintains priority: shortest duration first, then smallest index
   
5. **Process Task**:
   - Pop the top task from heap (shortest processing time)
   - Add its index to result
   - Advance `cur_time` by the task's processing time

**Time Complexity**: O(n log n)
- Sorting: O(n log n)
- Each task is pushed and popped from heap once: O(n log n)

**Space Complexity**: O(n)
- Heap can contain up to n tasks
- Augmented tasks list: O(n)

**Python Implementation:**
```python
import heapq

class Solution:
    def getOrder(self, tasks: List[List[int]]) -> List[int]:
        n = len(tasks)
        # Augment with original index: (enqueueTime, processingTime, index)
        tasks = [(start, dur, i) for i, (start, dur) in enumerate(tasks)]
        tasks.sort(key=lambda x: x[0])  # Sort by enqueue time

        res = []
        pq = []  # Min heap: (processingTime, index)
        i = 0
        cur_time = 0
        
        while i < n or pq:
            # If no tasks available, jump to next task's enqueue time
            if not pq and cur_time < tasks[i][0]:
                cur_time = tasks[i][0]

            # Add all tasks that are available at cur_time
            while i < n and tasks[i][0] <= cur_time:
                start_time, dur, idx = tasks[i]
                heapq.heappush(pq, (dur, idx))
                i += 1

            # Process task with shortest duration (and smallest index)
            dur, idx = heapq.heappop(pq)
            res.append(idx)
            cur_time += dur
            
        return res
```

**Why This Works:**
- Sorting ensures we consider tasks in chronological order of availability
- Min heap ensures we always pick the optimal task (shortest duration, smallest index)
- Time simulation correctly handles gaps when CPU would be idle

# Tags
`Heap`, `Priority Queue`, `Simulation`, `Sorting`, `Greedy`

