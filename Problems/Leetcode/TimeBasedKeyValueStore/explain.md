## Problem

**LeetCode 981: Time-Based Key-Value Store**

https://leetcode.com/problems/time-based-key-value-store/description/

### Problem Statement

Design a time-based key-value data structure that supports storing multiple values for the same key at different timestamps and retrieving values based on a query timestamp.

Implement the `TimeMap` class with:
- `__init__()`: Initialize the data structure
- `set(key: str, value: str, timestamp: int)`: Store a key-value pair with a timestamp
- `get(key: str, timestamp: int)`: Return the value associated with the key at or before the given timestamp

**Key Requirements:**
- Return the value associated with the **largest timestamp ≤ query timestamp**
- If no such value exists, return `""`
- All timestamps for `set()` operations on the same key are **strictly increasing**

### Example

```
timeMap = TimeMap()
timeMap.set("foo", "bar", 1)      # Store foo=bar at t=1
timeMap.get("foo", 1)              # Returns "bar" (exact match)
timeMap.get("foo", 3)              # Returns "bar" (t=1 is closest before t=3)
timeMap.set("foo", "bar2", 4)     # Store foo=bar2 at t=4
timeMap.get("foo", 4)              # Returns "bar2" (exact match)
timeMap.get("foo", 5)              # Returns "bar2" (t=4 is closest before t=5)
```

### Constraints

- `1 ≤ key.length, value.length ≤ 100`
- Key and value consist of lowercase English letters and digits
- `1 ≤ timestamp ≤ 10^7`
- All timestamps of `set()` are strictly increasing (per key)
- At most `2 × 10^5` calls to `set()` and `get()`

---

## Observations

### Key Insights

1. **Ordered Timestamps Per Key**: Since timestamps are strictly increasing for each key, we can maintain a sorted list of (timestamp, value) pairs for each key.

2. **Binary Search Opportunity**: For each `get()` query, we need to find the largest timestamp ≤ query timestamp. This is a classic **binary search** problem - finding the rightmost element ≤ target value.

3. **Time Complexity Trade-off**:
   - Without preprocessing: `set()` is O(1), but `get()` would be O(n) for linear search
   - With binary search: `set()` is O(1), `get()` is O(log n) - much better for the constraint of up to 2×10^5 operations

4. **Space Efficiency**: We store all (timestamp, value) pairs, which uses O(total calls) space.

### Algorithm Choice

Use a **HashMap + Binary Search** approach:
- Map each key to a list of (timestamp, value) tuples
- For `set()`: append to the key's list (O(1) since timestamps are strictly increasing)
- For `get()`: use binary search to find the position where we would insert the query timestamp, then backtrack to get the value at the previous timestamp

---

## Solution

### Approach: Binary Search on Sorted Timestamps

```python
class TimeMap:
    def __init__(self):
        # key -> list of (timestamp, value) tuples
        self.data = {}

    def set(self, key: str, value: str, timestamp: int) -> None:
        """Store key-value pair with timestamp"""
        if key not in self.data:
            self.data[key] = []
        self.data[key].append((timestamp, value))

    def get(self, key: str, timestamp: int) -> str:
        """Retrieve value for key at or before given timestamp"""
        
        def binary_search(arr, t):
            """
            Find position where timestamp t would be inserted.
            Returns the index of the first element > t.
            We then backtrack by 1 to get the largest element <= t.
            
            Args:
                arr: List of (timestamp, value) tuples (sorted by timestamp)
                t: Query timestamp
            
            Returns:
                Index of first element with timestamp > t
            """
            n = len(arr)
            left, right = 0, n - 1
            idx = n  # Default: no element <= t
            
            while left <= right:
                mid = left + (right - left) // 2
                
                if arr[mid][0] > t:
                    # arr[mid] is too large, but it's our current candidate
                    idx = mid
                    right = mid - 1
                else:
                    # arr[mid][0] <= t, this is valid, look right for larger
                    left = mid + 1
            
            return idx
        
        # Key doesn't exist
        if key not in self.data:
            return ""
        
        # Find first timestamp > query timestamp
        upper = binary_search(self.data[key], timestamp)
        
        # Backtrack to get the value at largest timestamp <= query
        upper -= 1
        if upper >= 0:
            return self.data[key][upper][1]
        
        return ""
```

### Detailed Walkthrough

#### Example: `get("foo", 3)` with timestamps [1, 4]

```
Binary Search for t=3:
arr = [(1, "bar"), (4, "bar2")]

Initial: left=0, right=1, idx=2

Iteration 1:
  mid = 0
  arr[0][0] = 1 <= 3, so left = 1

Iteration 2:
  mid = 1
  arr[1][0] = 4 > 3, so idx = 1, right = 0

Loop ends (left > right)
Return idx = 1

Backtrack: idx - 1 = 0
Return data[0][1] = "bar" ✓
```

#### Why This Binary Search Works

The binary search finds the **first element with timestamp > query timestamp**. Then:
- If we subtract 1 from this position, we get the **largest element ≤ query timestamp**
- If the result is negative, no valid value exists

---

### Complexity Analysis

| Operation | Time | Space |
|-----------|------|-------|
| `set()` | O(1) | O(1) per call |
| `get()` | O(log n) | - |
| **Overall** | O(m log n) | O(m) |

Where:
- `n` = number of timestamps for a given key
- `m` = total number of operations (up to 2×10^5)

**Why O(log n) for get()?**
- Binary search on a sorted list of timestamps: O(log n)
- Array lookup is O(1)

---

### Alternative: Python's `bisect` Module

Python provides built-in binary search through `bisect`:

```python
from bisect import bisect_right

class TimeMap:
    def __init__(self):
        self.data = {}

    def set(self, key: str, value: str, timestamp: int) -> None:
        if key not in self.data:
            self.data[key] = ([], [])  # (timestamps, values)
        self.data[key][0].append(timestamp)
        self.data[key][1].append(value)

    def get(self, key: str, timestamp: int) -> str:
        if key not in self.data:
            return ""
        
        timestamps, values = self.data[key]
        # bisect_right finds insertion point for timestamp
        # This gives us index of first timestamp > query
        idx = bisect_right(timestamps, timestamp) - 1
        
        if idx >= 0:
            return values[idx]
        return ""
```

This is more concise but uses separate lists for timestamps and values.

---

## Complexity Summary

- **Time**: O(1) for `set()`, O(log n) for `get()`
- **Space**: O(m) where m is total number of `set()` calls
- **Optimization**: Binary search reduces `get()` from O(n) to O(log n), crucial for up to 2×10^5 operations

---

# Tags

- Binary Search
- HashMap
- Time-Based Data Structure
- Leetcode Medium

