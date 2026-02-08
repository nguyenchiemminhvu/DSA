## Problem

https://leetcode.com/problems/process-tasks-using-servers/description/

```
You are given two 0-indexed integer arrays servers and tasks of lengths n and m respectively. 
servers[i] is the weight of the ith server, and tasks[j] is the time needed to process the jth task in seconds.

Tasks are assigned to the servers using a task queue. Initially, all servers are free, and the queue is empty.

At second j, the jth task is inserted into the queue (starting with the 0th task being inserted at second 0). 
As long as there are free servers and the queue is not empty, the task in the front of the queue will be 
assigned to a free server with the smallest weight, and in case of a tie, it is assigned to a free server 
with the smallest index.

If there are no free servers and the queue is not empty, we wait until a server becomes free and immediately 
assign the next task. If multiple servers become free at the same time, then multiple tasks from the queue 
will be assigned in order of insertion following the weight and index priorities above.

A server that is assigned task j at second t will be free again at second t + tasks[j].

Build an array ans of length m, where ans[j] is the index of the server the jth task will be assigned to.

Return the array ans.

Constraints:
- servers.length == n
- tasks.length == m
- 1 <= n, m <= 2 * 10^5
- 1 <= servers[i], tasks[j] <= 2 * 10^5

Example 1:
Input: servers = [3,3,2], tasks = [1,2,3,2,1,2]
Output: [2,2,0,2,1,2]

Example 2:
Input: servers = [5,1,4,3,2], tasks = [2,1,2,4,5,2,1]
Output: [1,4,1,4,1,3,2]
```

## Observations

1. **Scheduling Problem with Priority**: This is a task scheduling problem where we need to assign tasks to servers based on specific priority rules (weight, then index).

2. **Two States for Servers**: Servers can be in two states:
   - **Free**: Available to take new tasks, prioritized by (weight, index)
   - **Busy**: Processing a task, will become free at a specific time

3. **Time Progression**: Time doesn't always advance by 1 second:
   - Tasks arrive at their designated seconds (task j arrives at second j)
   - If no free servers are available, we must jump time forward to when the next server becomes free
   - Multiple tasks can be assigned at the same time if multiple servers become free simultaneously

4. **Queue Behavior**: Although the problem mentions a queue, we can process tasks directly since:
   - Tasks arrive in order (task j at second j)
   - We process them as soon as possible
   - No need for explicit queue data structure in most solutions

5. **Key Challenge**: Efficiently managing which servers are free and which are busy, and when busy servers become free.

## Solution

**Approach: Two Priority Queues (Min Heaps)**

Use two min-heaps to manage server states:

1. **Free Servers Heap (`free_heap`)**: 
   - Stores: `(weight, index)` for each free server
   - Min-heap ordered by weight first, then by index
   - Allows O(log n) access to the best available server

2. **Busy Servers Heap (`busy_heap`)**:
   - Stores: `(free_time, weight, index)` for each busy server
   - Min-heap ordered by free_time
   - Allows O(log n) to find when next server becomes available

**Algorithm Steps**:

```
Initialize:
- cur_time = 0
- Add all servers to free_heap as (weight, index)
- busy_heap = empty
- result = []

For each task j with duration tasks[j]:
    1. Update current time:
       cur_time = max(cur_time, j)  // Task j arrives at second j
    
    2. Free up servers that finished:
       While busy_heap is not empty AND busy_heap.top().free_time <= cur_time:
           server = busy_heap.pop()
           free_heap.push((server.weight, server.index))
    
    3. Handle case when no servers are free:
       If free_heap is empty:
           // Jump time to when next server becomes free
           cur_time = busy_heap.top().free_time
           // Free all servers that finish at this time
           While busy_heap.top().free_time == cur_time:
               server = busy_heap.pop()
               free_heap.push((server.weight, server.index))
    
    4. Assign task to best available server:
       weight, server_index = free_heap.pop()
       result[j] = server_index
       completion_time = cur_time + tasks[j]
       busy_heap.push((completion_time, weight, server_index))

Return result
```

**Time Complexity**: O((n + m) log n)
- Each of n servers can be moved between heaps multiple times
- Each of m tasks requires heap operations
- Each heap operation is O(log n)

**Space Complexity**: O(n)
- Two heaps storing at most n servers total
- Result array of size m (required for output)

**Key Insights**:
- The two-heap approach efficiently maintains the separation between free and busy servers
- Time can "jump" forward when waiting for servers, avoiding simulation of every second
- Sorting by (weight, index) in free_heap ensures correct priority selection
- Sorting by free_time in busy_heap allows efficient checking of which servers become available

### Python Implementation

```python
from typing import List
import heapq

class Solution:
    def assignTasks(self, servers: List[int], tasks: List[int]) -> List[int]:
        n = len(servers)
        m = len(tasks)
        res = [-1] * m  # Result: index of the server tasks[it] is assigned to
        
        # Free servers heap: (weight, index)
        # Min-heap ordered by weight first, then by index
        pq_server = [(servers[i], i) for i in range(n)]
        heapq.heapify(pq_server)
        
        # Busy servers heap: (available_time, weight, index)
        # Min-heap ordered by available_time (when server becomes free)
        pq_cooldown = []
        
        cur_time = 0  # Current simulation time
        
        for it in range(m):
            # Step 1: Update current time to when task 'it' arrives
            # Task 'it' arrives at second 'it'
            cur_time = max(cur_time, it)
            
            # Step 2: Free up all servers that have finished by cur_time
            while pq_cooldown and pq_cooldown[0][0] <= cur_time:
                _, w, idx = heapq.heappop(pq_cooldown)
                heapq.heappush(pq_server, (w, idx))
            
            # Step 3: If no servers are free, jump time to next available server
            if not pq_server:
                cur_time = pq_cooldown[0][0]  # Jump to when next server is free
                # Free all servers that become available at this time
                while pq_cooldown and pq_cooldown[0][0] <= cur_time:
                    _, w, idx = heapq.heappop(pq_cooldown)
                    heapq.heappush(pq_server, (w, idx))
            
            # Step 4: Assign task to the best available server
            w, idx = heapq.heappop(pq_server)
            res[it] = idx
            # Mark server as busy until cur_time + tasks[it]
            heapq.heappush(pq_cooldown, (cur_time + tasks[it], w, idx))
        
        return res
```

**Code Walkthrough with Example 1**:
```
servers = [3,3,2], tasks = [1,2,3,2,1,2]
Server weights: server 0=3, server 1=3, server 2=2

Initial: pq_server = [(2,2), (3,0), (3,1)], pq_cooldown = []

Task 0 (duration=1, arrives at t=0):
  cur_time = 0
  No servers to free
  Assign to server 2 (weight=2, lowest)
  pq_cooldown = [(1,2,2)]
  Result: [2]

Task 1 (duration=2, arrives at t=1):
  cur_time = 1
  Free server 2 (available at t=1)
  Assign to server 2 (weight=2, best available)
  pq_cooldown = [(3,2,2)]
  Result: [2,2]

Task 2 (duration=3, arrives at t=2):
  cur_time = 2
  No servers to free (server 2 free at t=3)
  Assign to server 0 (weight=3, best available)
  pq_cooldown = [(3,2,2), (5,3,0)]
  Result: [2,2,0]

Task 3 (duration=2, arrives at t=3):
  cur_time = 3
  Free server 2 (available at t=3)
  Assign to server 2
  pq_cooldown = [(5,2,2), (5,3,0)]
  Result: [2,2,0,2]

Task 4 (duration=1, arrives at t=4):
  cur_time = 4
  No servers to free
  Assign to server 1 (weight=3, best available)
  pq_cooldown = [(5,1,1), (5,2,2), (5,3,0)]
  Result: [2,2,0,2,1]

Task 5 (duration=2, arrives at t=5):
  cur_time = 5
  Free servers 0, 1, 2 (all available at t=5)
  Assign to server 2 (weight=2, lowest weight)
  Result: [2,2,0,2,1,2]
```

# Tags
#priority-queue #heap #simulation #greedy #scheduling

