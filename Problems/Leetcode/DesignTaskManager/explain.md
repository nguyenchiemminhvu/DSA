## Problem

https://leetcode.com/problems/design-task-manager/description/

Design a task management system that efficiently handles task operations based on priority. The system must support:
- Adding tasks with user-task-priority associations
- Modifying task priorities
- Removing tasks
- Executing the highest priority task (with highest taskId as tiebreaker)

**Key Requirements:**
- Multiple tasks can be assigned to the same user
- `execTop()` must return the userId of the executed task
- When multiple tasks share the highest priority, execute the one with the highest taskId
- All operations must be efficient given constraints: up to 10^5 initial tasks and 2*10^5 total operations

## Observations

1. **Priority Queue is Natural Fit**: We need to repeatedly find and remove the maximum priority task → Max heap data structure

2. **Tiebreaker Requirement**: When priorities are equal, we need highest taskId → Store tuples `(-priority, -taskId)` in min heap to simulate max heap behavior

3. **Edit/Remove Challenge**: Heap doesn't support efficient arbitrary element modification or deletion
   - Removing specific element: O(n) time
   - Updating priority: O(n) to find + O(log n) to reheapify
   
4. **Lazy Deletion Pattern**: Instead of actually modifying/removing from heap:
   - On `edit()`: Push new entry with updated priority, old entry becomes "stale"
   - On `rmv()`: Just remove from map, heap entry becomes "stale"
   - On `execTop()`: Clean up stale entries by validating against map

5. **Validation Strategy**: An entry `(-priority, -taskId)` in heap is valid if:
   - `taskId` exists in `task_map`
   - `priority` matches current priority in `task_map[taskId]`

6. **Time Complexity Trade-off**:
   - Lazy deletion adds O(log n) stale entries but avoids O(n) removal
   - Cleanup happens during `execTop()` which amortizes the cost
   - Each task can have at most O(k) stale entries where k = number of edits

## Solution

### Approach: Hash Map + Max Heap with Lazy Deletion

**Data Structures:**
1. `task_map`: Dict[taskId → (priority, userId)]
   - Single source of truth for current task state
   - O(1) lookup to validate heap entries
   
2. `pq`: Min heap of (-priority, -taskId)
   - Negation simulates max heap
   - May contain stale entries from edit/remove operations

**Operations:**

**`add(userId, taskId, priority)`** - O(log n)
```
- Add to task_map
- Push to heap
```

**`edit(taskId, newPriority)`** - O(log n)
```
- Update task_map with new priority
- Push new entry to heap (old entry becomes stale)
- Don't remove old entry (lazy deletion)
```

**`rmv(taskId)`** - O(1)
```
- Remove from task_map only
- Don't touch heap (lazy deletion)
```

**`execTop()`** - O(k log n) where k = stale entries at top
```
- While heap not empty:
    - Peek top entry
    - If stale (not in map OR priority mismatch):
        - Pop and continue (cleanup)
    - Else:
        - Valid entry found, break
- If heap empty: return -1
- Pop top entry
- Get userId from task_map
- Remove from task_map
- Return userId
```

**Why Lazy Deletion Works:**
1. Stale entries naturally percolate to top during pops
2. Cleanup cost amortizes: each task can only create limited stale entries
3. Avoids expensive O(n) heap modification operations
4. Map provides O(1) validation of heap entries

**Time Complexity:**
- `__init__`: O(n log n) where n = initial tasks
- `add`: O(log n)
- `edit`: O(log n) 
- `rmv`: O(1)
- `execTop`: O(log n) amortized (may need to pop multiple stale entries)

**Space Complexity:** O(n + m) where n = active tasks, m = stale heap entries
- Worst case: O(n * edits_per_task) if many edits, but bounded by total operations

# Tags
`Heap` `Priority Queue` `Hash Map` `Design` `Lazy Deletion` `Amortized Analysis`

