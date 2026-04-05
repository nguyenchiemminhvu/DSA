## Problem

https://leetcode.com/problems/snapshot-array/

Implement a `SnapshotArray` class that:
- **Constructor**: Initialize an array-like data structure with a given `length`. All elements are initially 0.
- **`set(index, val)`**: Set the element at `index` to `val`.
- **`snap()`**: Take a snapshot of the current array state and return a `snap_id` (the number of times `snap()` was called minus 1).
- **`get(index, snap_id)`**: Return the value at `index` from the snapshot with ID `snap_id`.

**Constraints**:
- 1 ≤ length ≤ 5 × 10⁴
- 0 ≤ index < length
- 0 ≤ val ≤ 10⁹
- 0 ≤ snap_id < (total number of snap() calls)
- At most 5 × 10⁴ calls to set, snap, and get

**Example**:
```
SnapshotArray snapshotArr = new SnapshotArray(3);
snapshotArr.set(0, 5);     // array[0] = 5
snapshotArr.snap();         // returns 0, captures [5, 0, 0]
snapshotArr.set(0, 6);      // array[0] = 6
snapshotArr.get(0, 0);      // returns 5 (from snap_id=0)
```

## Observations

1. **Naive approach is inefficient**: Storing the entire array at each snapshot would require O(n) space per snapshot, leading to O(n × m) total space where m is the number of snapshots. With up to 5 × 10⁴ operations and potentially many snapshots, this is wasteful.

2. **Sparse updates**: The key insight is that most indices won't change between snapshots. We typically only update a small fraction of the array before each snapshot.

3. **Only store changes**: Instead of storing the entire array, we can store only the indices that were modified, paired with their snapshot IDs and values. This is like a "versioned map" or "time-traveling hash map."

4. **Binary search for lookup**: For each index, we maintain a history of `[snap_id, value]` pairs. To get a value at a specific snap_id, we use binary search to find the most recent value before or at that snapshot ID.

5. **Space optimization**: If only k indices are ever modified (k ≤ total operations), we use O(k) space total instead of O(n × m).

## Solution

### Approach: Versioned Hash Map with Binary Search

**Data Structure**:
- For each index, maintain a list of `[snap_id, value]` pairs representing all changes to that index.
- Initially, seed each index with `[0, 0]` to represent the default value at snap_id=0.

**Algorithm**:

1. **`set(index, val)`**:
   - Check if the last recorded change for `index` is from the current `snap_id`.
   - If yes, update its value (modify in-place).
   - If no, append a new `[snap_id, val]` pair (this index is being modified for the first time in this snapshot).
   - Time: O(1)

2. **`snap()`**:
   - Increment `snap_id` and return the previous ID.
   - Time: O(1)

3. **`get(index, snap_id)`**:
   - Use binary search to find a `[snap_id_i, value]` pair in the history of `index`.
   - Lower bound finds the first entry with `snap_id_i ≥ snap_id`.
   - If exact match exists, return that value.
   - Otherwise, return the value from the previous entry (last known value at or before that snapshot).
   - Time: O(log k) where k is the number of changes to that index.

### Code Explanation

```python
class SnapshotArray:
    def __init__(self, length: int):
        self.n = length
        self.snap_id = 0
        # For each index, maintain a list of [snap_id, value] pairs
        # Initialize with [0, 0] as the base case (default value of 0 at snapshot 0)
        self.snaps = [[[0, 0]] for _ in range(length)]

    def set(self, index: int, val: int) -> None:
        # Check if we already modified this index in the current snapshot
        if self.snaps[index][-1][0] == self.snap_id:
            # If yes, just update the value (replace the most recent entry)
            self.snaps[index][-1][1] = val
        else:
            # If no, append a new [snap_id, val] entry
            self.snaps[index].append([self.snap_id, val])

    def snap(self) -> int:
        # Record current snapshot ID and move to the next one
        self.snap_id += 1
        return self.snap_id - 1

    def get(self, index: int, snap_id: int) -> int:
        # Binary search to find the value at the given snapshot
        def lower_bound(arr, target):
            left, right = 0, len(arr)
            while left < right:
                mid = (left + right) // 2
                if arr[mid][0] < target:
                    left = mid + 1
                else:
                    right = mid
            return left
        
        arr = self.snaps[index]
        idx = lower_bound(arr, snap_id)
        
        # If we found an exact match, return it
        if idx < len(arr) and arr[idx][0] == snap_id:
            return arr[idx][1]
        # Otherwise, return the value from the previous snapshot
        return arr[idx - 1][1]
```

### Complexity Analysis

- **Time**:
  - `__init__`: O(n)
  - `set`: O(1) amortized
  - `snap`: O(1)
  - `get`: O(log k) where k ≤ number of modifications to that index
  
- **Space**: O(k) where k ≤ total number of `set` operations (not O(n × m) like a naive approach)

### Why This Works

The solution exploits the sparsity of updates. If an index is never modified, we never store anything extra for it. We only pay for changes that actually happen. The binary search allows efficient lookup of historical values without reconstructing the entire snapshot.

# Tags
- Hash Map / Dictionary
- Binary Search
- Space Optimization
- Versioning / Snapshot Pattern

