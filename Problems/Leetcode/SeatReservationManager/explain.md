## Problem

https://leetcode.com/problems/seat-reservation-manager/description/

Design a system that manages the reservation state of `n` seats that are numbered from `1` to `n`.

Implement the `SeatManager` class:

- `SeatManager(int n)`: Initializes a SeatManager object that will manage `n` seats numbered from `1` to `n`. All seats are initially available.
- `int reserve()`: Fetches the smallest-numbered unreserved seat, reserves it, and returns its number.
- `void unreserve(int seatNumber)`: Unreserves the seat with the given `seatNumber`.

### Example

```
Input:
["SeatManager", "reserve", "reserve", "unreserve", "reserve", "reserve", "reserve", "reserve", "unreserve"]
[[5], [], [], [2], [], [], [], [], [5]]

Output:
[null, 1, 2, null, 2, 3, 4, 5, null]

Explanation:
SeatManager seatManager = new SeatManager(5); // Initializes with 5 seats
seatManager.reserve();    // Returns 1 (lowest available)
seatManager.reserve();    // Returns 2 (lowest available)
seatManager.unreserve(2); // Seat 2 is now available again
seatManager.reserve();    // Returns 2 (lowest available)
seatManager.reserve();    // Returns 3 (lowest available)
seatManager.reserve();    // Returns 4 (lowest available)
seatManager.reserve();    // Returns 5 (only available)
seatManager.unreserve(5); // Seat 5 is now available again
```

### Constraints

- `1 <= n <= 10^5`
- `1 <= seatNumber <= n`
- For each call to `reserve`, there will be at least one unreserved seat
- For each call to `unreserve`, `seatNumber` will be reserved
- At most `10^5` calls in total will be made to `reserve` and `unreserve`

## Observations

1. **Always need the minimum**: The `reserve()` operation always needs to return the smallest available seat number.

2. **Dynamic availability**: Seats can become available again through `unreserve()`, so we need to dynamically track available seats.

3. **Efficiency requirements**: With up to `10^5` operations, we need efficient data structure operations:
   - Quick retrieval of minimum element
   - Quick insertion of newly available seats

4. **Min-heap is ideal**: A min-heap (priority queue) naturally maintains the smallest element at the top and supports:
   - `O(log n)` insertion
   - `O(log n)` extraction of minimum
   - `O(1)` access to minimum

5. **Simple state tracking**: We only need to track which seats are currently available, not which are reserved.

## Solution

### Approach: Min-Heap (Priority Queue)

The solution uses a min-heap to store all available seat numbers. The heap property ensures the smallest available seat is always at the top.

```python
import heapq

class SeatManager:

    def __init__(self, n: int):
        # Initialize heap with all seats [1, 2, 3, ..., n]
        self.pq = [i + 1 for i in range(n)]

    def reserve(self) -> int:
        # Pop and return the smallest available seat
        return heapq.heappop(self.pq)

    def unreserve(self, seatNumber: int) -> None:
        # Push the seat back into the heap
        heapq.heappush(self.pq, seatNumber)
```

### How It Works

1. **Initialization (`__init__`)**:
   - Create a list `[1, 2, 3, ..., n]` representing all seats
   - Python lists are already valid min-heaps when created in ascending order
   - All seats start as available

2. **Reserve (`reserve`)**:
   - Use `heapq.heappop()` to remove and return the minimum element
   - This automatically maintains the heap property
   - The popped seat is now "reserved" (removed from available pool)

3. **Unreserve (`unreserve`)**:
   - Use `heapq.heappush()` to add the seat back to the heap
   - This automatically places it in the correct position
   - The seat is now available again

### Example Walkthrough

```
Initial: heap = [1, 2, 3, 4, 5]

reserve() → pop 1 → heap = [2, 3, 4, 5] → return 1
reserve() → pop 2 → heap = [3, 4, 5] → return 2
unreserve(2) → push 2 → heap = [2, 3, 4, 5]
reserve() → pop 2 → heap = [3, 4, 5] → return 2
reserve() → pop 3 → heap = [4, 5] → return 3
reserve() → pop 4 → heap = [5] → return 4
reserve() → pop 5 → heap = [] → return 5
unreserve(5) → push 5 → heap = [5]
```

### Complexity Analysis

**Time Complexity:**
- `__init__(n)`: `O(n)` to create the initial list
- `reserve()`: `O(log n)` for heap pop operation
- `unreserve(seatNumber)`: `O(log n)` for heap push operation

**Space Complexity:**
- `O(n)` to store all available seats in the heap
- In the worst case, all `n` seats remain available

### Why This Approach Works

1. **Correctness**: The min-heap always maintains the smallest available seat at the top, satisfying the requirement to return the smallest-numbered unreserved seat.

2. **Efficiency**: Heap operations are logarithmic, which is efficient enough for the constraint of `10^5` operations.

3. **Simplicity**: The solution is straightforward with minimal state management—just one data structure tracking available seats.

### Alternative Approaches (Not Implemented)

1. **Sorted Set**: Could use a balanced BST or sorted container
   - Similar time complexity
   - More complex to implement from scratch

2. **Boolean Array**: Track reserved/unreserved status
   - `O(n)` time for each `reserve()` to find minimum
   - Not efficient enough

3. **Set + Variable**: Track next unreserved seat + set of freed seats
   - More complex state management
   - Similar performance to heap

The min-heap approach strikes the best balance between simplicity, correctness, and efficiency.

# Tags

`Heap`, `Priority Queue`, `Design`, `Min-Heap`

