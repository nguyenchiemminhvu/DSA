## Problem Description

https://leetcode.com/problems/design-hashset/description/

```
Design a HashSet without using any built-in hash table libraries.

Implement MyHashSet class:

void add(key) Inserts the value key into the HashSet.
bool contains(key) Returns whether the value key exists in the HashSet or not.
void remove(key) Removes the value key in the HashSet. If key does not exist in the HashSet, do nothing.

Example 1:

Input
["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
[[], [1], [2], [1], [3], [2], [2], [2], [2]]
Output
[null, null, null, true, false, null, true, null, false]

Explanation
MyHashSet myHashSet = new MyHashSet();
myHashSet.add(1);      // set = [1]
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(1); // return True
myHashSet.contains(3); // return False, (not found)
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(2); // return True
myHashSet.remove(2);   // set = [1]
myHashSet.contains(2); // return False, (already removed)

Constraints:

0 <= key <= 106
At most 104 calls will be made to add, remove, and contains.
```

## Observations

When designing a hash set from scratch, we need to understand the fundamental concepts:

### What is a Hash Set?
A hash set is a data structure that stores **unique** values and provides fast operations:
- **Add**: Insert a value (O(1) average time)
- **Remove**: Delete a value (O(1) average time)
- **Contains**: Check if a value exists (O(1) average time)

### Key Challenges
1. **Hash Function**: We need a way to convert any key into an array index
2. **Collision Handling**: Different keys might hash to the same index
3. **Dynamic Resizing**: As we add more elements, we need to maintain performance
4. **Load Factor**: Keep the ratio of elements to table size reasonable

### Design Decisions
- **Separate Chaining**: Use lists (buckets) at each table index to handle collisions
- **Dynamic Resizing**: When load factor exceeds 0.75, double the table size
- **Hash Function**: Use Python's built-in `hash()` function with modulo operation

## Solution

### Approach: Hash Table with Separate Chaining

Our solution uses a **two-class design**:
1. `HashTable`: A general-purpose hash table that can store key-value pairs
2. `MyHashSet`: A wrapper that uses the hash table specifically for set operations

### HashTable Class Implementation

```python
class HashTable:
    def __init__(self, init_size = 16):
        self._size = 0  # Number of elements stored
        self._table = [[] for _ in range(0, init_size)]  # Array of empty lists (buckets)
```

**Key Components:**

#### 1. Hash Function
```python
def _hash_key(self, key: Any) -> int:
    return hash(key) % len(self._table)
```
- Converts any key to a valid table index
- Uses modulo to ensure index is within table bounds
- Example: `hash(42) % 16` might return `10`

#### 2. Load Factor Management
```python
def _get_factor(self) -> float:
    return self._size / len(self._table)
```
- Measures how "full" our table is
- When > 0.75, we resize to maintain performance
- Example: 12 elements in 16 slots = 0.75 load factor

#### 3. Dynamic Resizing
```python
def _resize_table(self, new_size: int) -> None:
    new_table = [[] for _ in range(0, new_size)]
    for bucket in self._table:
        for (key, value) in bucket:
            new_bucket_index = hash(key) % new_size  # Rehash for new size
            new_table[new_bucket_index].append((key, value))
    self._table = new_table
```
- Creates a new, larger table
- **Rehashes all existing elements** (important: indices change with new table size!)
- Maintains all data while improving performance

#### 4. Insert Operation
```python
def insert(self, key: Any, val: Any) -> None:
    if self._get_factor() > 0.75:
        self._resize_table(len(self._table) * 2)  # Resize if needed
    
    bucket_index = self._hash_key(key)
    bucket = self._table[bucket_index]
    
    # Check if key already exists and update it
    for i, (k, v) in enumerate(bucket):
        if k == key:
            bucket[i] = (key, val)  # Update existing key
            return
    
    # If key doesn't exist, add new entry
    bucket.append((key, val))
    self._size += 1
```

**Step-by-step process:**
1. Check if resize is needed
2. Find the correct bucket using hash function
3. Search bucket for existing key (update if found)
4. If not found, add new key-value pair

#### 5. Remove Operation
```python
def remove(self, key: Any) -> None:
    bucket_index = self._hash_key(key)
    bucket = self._table[bucket_index]
    for (k, v) in bucket:
        if k == key:
            bucket.remove((k, v))
            self._size -= 1
            return
```

#### 6. Contains Operation
```python
def contains(self, key: Any) -> bool:
    bucket_index = self._hash_key(key)
    bucket = self._table[bucket_index]
    for (k, v) in bucket:
        if k == key:
            return True
    return False
```

### MyHashSet Implementation

```python
class MyHashSet:
    def __init__(self):
        self._hash_table = HashTable()

    def add(self, key: int) -> None:
        self._hash_table.insert(key, True)  # Use True as dummy value

    def remove(self, key: int) -> None:
        self._hash_table.remove(key)

    def contains(self, key: int) -> bool:
        return self._hash_table.contains(key)
```

**Design Choice**: Since we only need to track existence (not values), we use `True` as a dummy value for all keys.

### Example Walkthrough

Let's trace through the example:

1. `MyHashSet()`: Creates hash table with 16 empty buckets
2. `add(1)`: 
   - `hash(1) % 16 = 1` → Store `(1, True)` in bucket[1]
3. `add(2)`:
   - `hash(2) % 16 = 2` → Store `(2, True)` in bucket[2]
4. `contains(1)`:
   - `hash(1) % 16 = 1` → Check bucket[1] → Find `(1, True)` → Return `True`
5. `contains(3)`:
   - `hash(3) % 16 = 3` → Check bucket[3] → Empty → Return `False`

### Time Complexity Analysis

- **Average Case**: O(1) for all operations
  - Hash function: O(1)
  - Bucket operations: O(1) when load factor is reasonable
- **Worst Case**: O(n) when all keys hash to same bucket
- **Amortized**: O(1) due to dynamic resizing

### Space Complexity
- **Space**: O(n) where n is the number of unique keys stored

### Why This Solution Works

1. **Collision Handling**: Separate chaining handles hash collisions gracefully
2. **Performance**: Load factor management keeps operations fast
3. **Scalability**: Dynamic resizing allows unlimited growth
4. **Simplicity**: Clean interface that's easy to understand and maintain

This implementation demonstrates fundamental hash table concepts while providing excellent practical performance for the hash set problem.



## Tags

array, hash table