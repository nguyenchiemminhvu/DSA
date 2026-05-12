## Problem

https://leetcode.com/problems/lru-cache/description

Design a data structure that follows the constraints of a **Least Recently Used (LRU) cache**.

### Operations

**LRUCache(int capacity)** - Initialize the LRU cache with positive size capacity.

**int get(int key)** - Return the value of the key if the key exists, otherwise return -1.

**void put(int key, int value)** - Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.

### Constraints

- Both `get` and `put` must run in **O(1) average time complexity**
- 1 ≤ capacity ≤ 3000
- 0 ≤ key ≤ 10⁴
- 0 ≤ value ≤ 10⁵
- At most 2 × 10⁵ calls will be made to `get` and `put`

### Example

```
Input:  ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
        [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output: [null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation:
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1);     // cache is {1=1}
lRUCache.put(2, 2);     // cache is {1=1, 2=2}
lRUCache.get(1);        // return 1
lRUCache.put(3, 3);     // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);        // returns -1 (not found)
lRUCache.put(4, 4);     // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);        // return -1 (not found)
lRUCache.get(3);        // return 3
lRUCache.get(4);        // return 4
```

## Observations

### Key Insights

1. **O(1) Requirement**: We need both **O(1) lookup** and **O(1) insertion/deletion** along with **tracking access order**.

2. **Data Structure Combination**:
   - **Hash Map (Dictionary)**: Provides O(1) key-value lookup
   - **Doubly Linked List**: Maintains insertion/access order while allowing O(1) removal from any position

3. **Access Order Tracking**:
   - Most recently used items move to the front (right after head)
   - Least recently used items stay at the back (right before tail)
   - When capacity is exceeded, we remove the node at the back (closest to tail)

4. **Operations on Doubly Linked List**:
   - `__remove(node)`: Remove node from middle of list - O(1) with direct reference
   - `__insert(node)`: Insert node at position - O(1) with pointer manipulation

5. **Put vs Get**:
   - `get(key)`: If found, move to most recent position
   - `put(key, value)`: 
     - If key exists, update value and move to most recent
     - If key doesn't exist, create new node
     - Check if capacity exceeded and evict LRU node

### Why This Approach Works

- **Dummy Nodes**: The head and tail dummy nodes simplify boundary conditions:
  - No need to check for null pointers
  - Circular-like structure: head.prev points to tail, tail.next points to head
  - Always have valid prev/next references

- **Order Maintenance**:
  ```
  tail.next -> [MRU] -> [MRU] -> ... -> [LRU] -> head.prev
  ^                                                    |
  |____________________________________________________|
  ```
  - Most recently used nodes are inserted next to head (on the left)
  - Least recently used nodes are near tail (on the right)
  - Eviction always removes tail.next (the LRU node)

## Solution

```python
class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.prev = self.next = None

class LRUCache:

    def __init__(self, capacity: int):
        """
        Initialize cache with capacity and dummy nodes for doubly linked list.
        """
        self.cap = capacity
        self.cache = {}  # key -> Node(key, value)
        
        # Dummy nodes - simplify edge cases
        self.head, self.tail = Node(0, 0), Node(0, 0)
        # Create circular structure: head <-> tail
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def __insert(self, node: Node):
        """
        Insert node right after head (most recent position).
        O(1) operation.
        """
        prv = self.head.next  # Current first node
        prv.prev = node       # Link back
        node.next = prv       # Link forward
        self.head.next = node # Point head to new node
        node.prev = self.head # Link back to head
    
    def __remove(self, node: Node):
        """
        Remove node from doubly linked list.
        O(1) operation with direct reference.
        """
        prv, nxt = node.prev, node.next
        prv.next = nxt
        nxt.prev = prv

    def get(self, key: int) -> int:
        """
        Get value for key and mark as most recently used.
        Time: O(1)
        """
        if key in self.cache:
            val = self.cache[key].value
            # Move to most recent position
            self.__remove(self.cache[key])
            self.__insert(self.cache[key])
            return val
        return -1

    def put(self, key: int, value: int) -> None:
        """
        Put key-value pair and evict LRU if capacity exceeded.
        Time: O(1)
        """
        # If key already exists, remove old node
        if key in self.cache:
            self.__remove(self.cache[key])

        # Create new node and insert
        node = Node(key, value)
        self.cache[key] = node
        self.__insert(node)
        
        # Check capacity and evict LRU if needed
        if len(self.cache) > self.cap:
            # LRU node is the one closest to tail
            lru = self.tail.prev
            self.__remove(lru)
            self.cache.pop(lru.key)
```

### Time & Space Complexity

| Operation | Time | Space |
|-----------|------|-------|
| `__init__` | O(1) | O(1) |
| `get` | O(1) | - |
| `put` | O(1) | O(1) |
| **Overall** | **O(1)** | **O(capacity)** |

### Algorithm Trace

For the example with capacity = 2:

| Operation | Cache State | Linked List (head → tail) | Note |
|-----------|-------------|---------------------------|------|
| `put(1, 1)` | {1: 1} | 1 | Insert 1 |
| `put(2, 2)` | {1: 1, 2: 2} | 2 ↔ 1 | Insert 2, move to front |
| `get(1)` | {1: 1, 2: 2} | 1 ↔ 2 | Access 1, move to front |
| `put(3, 3)` | {1: 1, 3: 3} | 3 ↔ 1 | Insert 3, evict LRU (2) |
| `get(2)` | {1: 1, 3: 3} | - | Not found, return -1 |
| `put(4, 4)` | {3: 3, 4: 4} | 4 ↔ 3 | Insert 4, evict LRU (1) |
| `get(1)` | {3: 3, 4: 4} | - | Not found, return -1 |
| `get(3)` | {3: 3, 4: 4} | 3 ↔ 4 | Access 3, move to front |
| `get(4)` | {3: 3, 4: 4} | 4 ↔ 3 | Access 4, move to front |

# Tags
#doubly-linked-list #hash-map #cache #design

