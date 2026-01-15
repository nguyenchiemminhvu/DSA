## Problem

https://leetcode.com/problems/design-a-number-container-system/

Design a number container system that can do the following:

- **Insert or Replace** a number at the given index in the system.
- **Return the smallest index** for the given number in the system.

Implement the `NumberContainers` class:

- `NumberContainers()` Initializes the number container system.
- `void change(int index, int number)` Fills the container at index with the number. If there is already a number at that index, replace it.
- `int find(int number)` Returns the smallest index for the given number, or -1 if there is no index that is filled by number in the system.

**Example 1:**
```
Input
["NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"]
[[], [10], [2, 10], [1, 10], [3, 10], [5, 10], [10], [1, 20], [10]]
Output
[null, -1, null, null, null, null, 1, null, 2]

Explanation
NumberContainers nc = new NumberContainers();
nc.find(10); // Returns -1 (no index contains 10)
nc.change(2, 10); // Index 2 now contains 10
nc.change(1, 10); // Index 1 now contains 10
nc.change(3, 10); // Index 3 now contains 10
nc.change(5, 10); // Index 5 now contains 10
nc.find(10); // Returns 1 (smallest index with 10)
nc.change(1, 20); // Index 1 now contains 20 (replaced 10)
nc.find(10); // Returns 2 (smallest remaining index with 10)
```

**Constraints:**
- 1 <= index, number <= 10^9
- At most 10^5 calls will be made in total to `change` and `find`.

## Observations

1. **Two-way Mapping Required**: We need to efficiently:
   - Track what number is at each index (for updates)
   - Track which indices contain each number (for queries)

2. **Min Heap for Smallest Index**: To find the smallest index efficiently, we can use a min heap for each number.

3. **Lazy Deletion Challenge**: When we change an index from one number to another, we need to handle "stale" indices in the heap:
   - Removing from middle of heap is O(n)
   - Instead, use **lazy deletion**: keep stale entries and clean them during `find()`

4. **Stale Entry Detection**: An index in the heap for number N is stale if:
   - The index no longer exists in `map_idx`, OR
   - The index now maps to a different number

5. **Time Complexity Goals**:
   - `change()`: O(log n) - heap push
   - `find()`: O(log n) amortized - pop stale entries until finding valid one

## Solution

### Approach: Hash Maps + Min Heaps with Lazy Deletion

**Data Structures:**
1. `map_idx`: Dictionary mapping `index -> current_number`
   - Tracks what number is currently at each index
   
2. `map_val`: Dictionary mapping `number -> min_heap_of_indices`
   - For each number, maintains a min heap of all indices that ever contained it
   - May contain stale entries (indices that have been changed)

**Algorithm:**

**`change(index, number)`:**
1. Update `map_idx[index] = number` (overwrites old value if exists)
2. Add `index` to the heap for `number` in `map_val`
   - Don't remove the old index from its previous number's heap (lazy deletion)

**`find(number)`:**
1. If `number` not in `map_val`, return -1
2. **Clean stale entries**: While the heap's top element is invalid:
   - An entry is invalid if:
     - The index doesn't exist in `map_idx`, OR
     - The index maps to a different number in `map_idx`
   - Pop the invalid entry
3. After cleaning, if heap is empty, return -1
4. Otherwise, return the top of the heap (smallest valid index)

### Why This Works

**Correctness:**
- `map_idx` always contains the current state (latest number at each index)
- `map_val` heaps may contain outdated indices, but `find()` validates before returning
- Lazy deletion ensures we don't waste time removing from middle of heaps

**Efficiency:**
- Each index can be added to heaps at most O(total calls) times
- Each added index is popped at most once
- Amortized time per operation: O(log n)

### Code

```python
import heapq

class NumberContainers:

    def __init__(self):
        self.map_idx = {}  # index -> current number
        self.map_val = {}  # number -> min heap of indices

    def change(self, index: int, number: int) -> None:
        # Update the current mapping
        self.map_idx[index] = number
        
        # Add this index to the heap for this number
        if number not in self.map_val:
            self.map_val[number] = [index]
        else:
            heapq.heappush(self.map_val[number], index)

    def find(self, number: int) -> int:
        # If number never seen, return -1
        if number not in self.map_val:
            return -1
        
        # Clean up stale entries from the heap
        # An entry is stale if:
        # 1. Index is in map_idx AND maps to a different number
        # (If index not in map_idx, it means it was never set, which shouldn't happen)
        while (self.map_val[number] and 
               self.map_val[number][0] in self.map_idx and 
               self.map_idx[self.map_val[number][0]] != number):
            heapq.heappop(self.map_val[number])
        
        # After cleaning, check if heap has valid entries
        if self.map_val[number]:
            return self.map_val[number][0]
        
        return -1
```

### Complexity Analysis

**Time Complexity:**
- `change()`: O(log n) where n is the number of indices for that number
  - Dictionary update: O(1)
  - Heap push: O(log n)
  
- `find()`: O(k log n) where k is the number of stale entries to remove
  - Amortized O(log n) because each index is pushed once and popped at most once
  
**Space Complexity:**
- O(m + n) where m is the number of unique indices and n is the total number of entries in all heaps
- In worst case, if we change each index multiple times to different numbers, space could be O(calls)
- But typically much better with lazy deletion than eager deletion

### Example Walkthrough

```
nc = NumberContainers()

nc.find(10) → -1
  map_val = {}
  
nc.change(2, 10)
  map_idx = {2: 10}
  map_val = {10: [2]}
  
nc.change(1, 10)
  map_idx = {2: 10, 1: 10}
  map_val = {10: [1, 2]}  // min heap
  
nc.change(3, 10)
  map_idx = {2: 10, 1: 10, 3: 10}
  map_val = {10: [1, 2, 3]}
  
nc.change(5, 10)
  map_idx = {2: 10, 1: 10, 3: 10, 5: 10}
  map_val = {10: [1, 2, 3, 5]}
  
nc.find(10) → 1
  Heap top is 1, map_idx[1] == 10 ✓
  Return 1
  
nc.change(1, 20)
  map_idx = {2: 10, 1: 20, 3: 10, 5: 10}
  map_val = {10: [1, 2, 3, 5], 20: [1]}
  // Note: 1 is still in heap for 10 (stale entry)
  
nc.find(10) → 2
  Heap top is 1, but map_idx[1] == 20 ≠ 10 ✗
  Pop 1
  Heap top is now 2, map_idx[2] == 10 ✓
  Return 2
```

# Tags
- Design
- Hash Table
- Heap (Priority Queue)
- Lazy Deletion

