## Problem

https://leetcode.com/problems/smallest-number-in-infinite-set/description/

You have a set which contains all positive integers [1, 2, 3, 4, 5, ...].

Implement the SmallestInfiniteSet class:

- `SmallestInfiniteSet()` Initializes the SmallestInfiniteSet object to contain all positive integers.
- `int popSmallest()` Removes and returns the smallest integer contained in the infinite set.
- `void addBack(int num)` Adds a positive integer num back into the infinite set, if it is not already in the infinite set.

**Example 1:**

```
Input
["SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest", "popSmallest", "addBack", "popSmallest", "popSmallest", "popSmallest"]
[[], [2], [], [], [], [1], [], [], []]
Output
[null, null, 1, 2, 3, null, 1, 4, 5]

Explanation
SmallestInfiniteSet smallestInfiniteSet = new SmallestInfiniteSet();
smallestInfiniteSet.addBack(2);    // 2 is already in the set, so no change is made.
smallestInfiniteSet.popSmallest(); // return 1, since 1 is the smallest number, and remove it from the set.
smallestInfiniteSet.popSmallest(); // return 2, and remove it from the set.
smallestInfiniteSet.popSmallest(); // return 3, and remove it from the set.
smallestInfiniteSet.addBack(1);    // 1 is added back to the set.
smallestInfiniteSet.popSmallest(); // return 1, since 1 was added back to the set and
                                   // is the smallest number, and remove it from the set.
smallestInfiniteSet.popSmallest(); // return 4, and remove it from the set.
smallestInfiniteSet.popSmallest(); // return 5, and remove it from the set.
```

**Constraints:**

- 1 <= num <= 1000
- At most 1000 calls will be made in total to popSmallest and addBack.

## Observations

1. **Set maintains uniqueness**: We need to track which numbers are currently in the set to prevent duplicates when adding back.

2. **Fast minimum retrieval**: We need to efficiently find and remove the smallest element, which suggests using a min-heap (priority queue).

3. **Bounded range**: The constraint `1 <= num <= 1000` means we can initialize with a finite set rather than truly infinite.

4. **Two operations**:
   - `popSmallest()`: Must return the minimum element in O(log n) time
   - `addBack()`: Must check existence in O(1) and insert in O(log n)

5. **Dual data structures needed**:
   - **Heap**: For efficient minimum element retrieval
   - **Set**: For O(1) membership checking to avoid duplicates

## Solution

### Approach: Min-Heap + Set

```python
import heapq

class SmallestInfiniteSet:

    def __init__(self):
        # Set for O(1) membership checking
        self.s = set([val for val in range(1, 1001)])
        # Min-heap for O(log n) minimum retrieval
        self.pq = [val for val in range(1, 1001)]

    def popSmallest(self) -> int:
        # Get and remove minimum from heap
        val = heapq.heappop(self.pq)
        # Remove from set to maintain consistency
        self.s.remove(val)
        return val

    def addBack(self, val: int) -> None:
        # Only add if not already present
        if val not in self.s:
            self.s.add(val)
            heapq.heappush(self.pq, val)
```

### Explanation

**Data Structures:**
- `self.s`: A set containing all available numbers (initially 1-1000)
- `self.pq`: A min-heap containing all available numbers (initially 1-1000)

**Constructor `__init__()`:**
- Initializes both set and heap with numbers from 1 to 1000
- Time: O(n) where n = 1000
- Space: O(n)

**`popSmallest()`:**
1. Use `heapq.heappop()` to remove and return the minimum element from the heap in O(log n)
2. Remove the same value from the set in O(1) to keep both structures synchronized
3. Return the popped value

**`addBack(val)`:**
1. Check if `val` is already in the set in O(1) time
2. If not present:
   - Add to set in O(1)
   - Push to heap in O(log n)
3. This ensures no duplicates are added

### Complexity Analysis

- **Time Complexity:**
  - `__init__()`: O(n) where n = 1000
  - `popSmallest()`: O(log n) for heap pop + O(1) for set removal = O(log n)
  - `addBack()`: O(1) for set check + O(log n) for heap push = O(log n)

- **Space Complexity:** O(n) for storing the set and heap, where n = 1000

### Why This Works

1. **Min-heap property**: Always gives us the smallest element in O(log n)
2. **Set membership**: Prevents duplicate additions in O(1) lookup time
3. **Synchronization**: Both structures are kept in sync - when we pop from heap, we remove from set; when we add back, we add to both
4. **Correctness**: The set ensures we never add duplicates, and the heap ensures we always get the minimum value

# Tags

- Heap / Priority Queue
- Set
- Design
- Data Structures

