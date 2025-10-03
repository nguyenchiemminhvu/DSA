## Problem Description

https://leetcode.com/problems/design-hashmap/description/

```
Design a HashMap without using any built-in hash table libraries.

Implement the MyHashMap class:

MyHashMap() initializes the object with an empty map.
void put(int key, int value) inserts a (key, value) pair into the HashMap. If the key already exists in the map, update the corresponding value.
int get(int key) returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
void remove(key) removes the key and its corresponding value if the map contains the mapping for the key.

Example 1:

Input
["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
Output
[null, null, null, 1, -1, null, 1, null, -1]

Explanation
MyHashMap myHashMap = new MyHashMap();
myHashMap.put(1, 1); // The map is now [[1,1]]
myHashMap.put(2, 2); // The map is now [[1,1], [2,2]]
myHashMap.get(1);    // return 1, The map is now [[1,1], [2,2]]
myHashMap.get(3);    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
myHashMap.put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
myHashMap.get(2);    // return 1, The map is now [[1,1], [2,1]]
myHashMap.remove(2); // remove the mapping for 2, The map is now [[1,1]]
myHashMap.get(2);    // return -1 (i.e., not found), The map is now [[1,1]]

Constraints:

0 <= key, value <= 106
At most 104 calls will be made to put, get, and remove.
```

## Observations

### Key Requirements Analysis
1. **No built-in hash table libraries** - We need to implement everything from scratch
2. **Three core operations**: `put()`, `get()`, `remove()`
3. **Key collision handling** - Multiple keys might hash to the same index
4. **Dynamic behavior** - Should handle updates to existing keys
5. **Performance expectations** - Should be efficient for up to 10^4 operations

### Design Considerations
1. **Collision Resolution Strategy**:
   - **Separate Chaining**: Each bucket holds a list of key-value pairs
   - **Open Addressing**: Find next available slot when collision occurs
   - *Choice*: Separate chaining is simpler to implement and handle deletions

2. **Hash Function**:
   - Need to map keys to array indices uniformly
   - Use modulo operation to fit within table size
   - Python's built-in `hash()` provides good distribution

3. **Dynamic Resizing**:
   - As elements increase, performance degrades due to longer chains
   - Monitor load factor (elements/buckets ratio)
   - Resize when load factor exceeds threshold (0.75 is common)

4. **Memory vs Performance Trade-off**:
   - Larger table = fewer collisions but more memory
   - Smaller table = more collisions but less memory
   - Dynamic resizing balances both

### Key Algorithm Steps:

**PUT Operation:**
1. Check if resize needed (load factor > 0.75)
2. Hash key to find bucket index
3. Search bucket for existing key
4. Update if found, otherwise append new pair
5. Increment size counter if new key added

**GET Operation:**
1. Hash key to find bucket index
2. Linear search through bucket for key
3. Return value if found, -1 if not found

**REMOVE Operation:**
1. Hash key to find bucket index
2. Search bucket for key-value pair
3. Remove pair if found and decrement size

**RESIZE Operation:**
1. Create new table with double the buckets
2. Rehash all existing key-value pairs
3. Place them in appropriate new buckets
4. Replace old table with new one

### Complexity Analysis:

| Operation | Average Case | Worst Case | Space |
|-----------|-------------|------------|-------|
| put()     | O(1)        | O(n)       | O(n)  |
| get()     | O(1)        | O(n)       | O(n)  |
| remove()  | O(1)        | O(n)       | O(n)  |

- **Average O(1)**: Good hash distribution spreads elements evenly
- **Worst O(n)**: All elements hash to same bucket (very rare)
- **Space O(n)**: Store n key-value pairs plus table overhead

## Tags

array, hash table