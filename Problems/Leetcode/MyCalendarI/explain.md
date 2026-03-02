## Problem

https://leetcode.com/problems/my-calendar-i/

````markdown
## Problem

https://leetcode.com/problems/my-calendar-i/

```
You are implementing a program to use as your calendar. We can add a new event
if adding the event will not cause a double booking.

A double booking happens when two events have some non-empty intersection
(i.e., some moment is common to both events).

The event can be represented as a pair of integers startTime and endTime that
represents a booking on the half-open interval [startTime, endTime), the range
of real numbers x such that startTime <= x < endTime.

Implement the MyCalendar class:
- MyCalendar() Initializes the calendar object.
- boolean book(int startTime, int endTime) Returns true if the event can be
  added to the calendar successfully without causing a double booking. Otherwise,
  return false and do not add the event to the calendar.

Example 1:
Input
["MyCalendar", "book", "book", "book"]
[[], [10, 20], [15, 25], [20, 30]]
Output
[null, true, false, true]

Explanation
MyCalendar myCalendar = new MyCalendar();
myCalendar.book(10, 20); // return True
myCalendar.book(15, 25); // return False, It can not be booked because time 15
                          // is already booked by another event.
myCalendar.book(20, 30); // return True, The event can be booked, as the first
                          // event takes every time less than 20, but not
                          // including 20.

Constraints:
- 0 <= start < end <= 10^9
- At most 1000 calls will be made to book.
```

## Observations

1. **Half-open intervals**: Each booking covers `[start, end)`. A moment `x` is covered
   by a booking if `start <= x < end`. Two bookings `[a, b)` and `[c, d)` overlap if
   and only if `a < d` and `c < b`. The problem asks us to prevent any moment from
   being covered by 2 or more overlapping bookings simultaneously.

2. **Difference Array / Sweep Line Technique**: Instead of checking every possible
   moment (which can be up to 10^9), we model the timeline as a sparse map of
   **change events**:
   - When a booking `[start, end)` is added, the "active booking count" increases by 1
     at `start` and decreases by 1 at `end`.
   - By sweeping through all recorded timestamps in sorted order and accumulating these
     deltas, we can compute the maximum concurrent bookings at any point in time.

3. **Sparse representation**: Since at most 1000 calls are made, there are at most
   2000 distinct timestamps. A `defaultdict(int)` efficiently stores only the relevant
   points without allocating memory for the whole `[0, 10^9]` range.

4. **Validation before committing**: To check whether a new event `[start, end)` causes
   a double booking, we **tentatively add** the deltas (`timeline[start] += 1`,
   `timeline[end] -= 1`), run the sweep, and if the running sum ever reaches 2, we
   **roll back** the changes and return `False`. If no violation is found, the booking
   stands and we return `True`.

5. **Why the sweep works**: The running prefix sum at any sorted timestamp equals the
   exact number of active bookings in the interval `[timestamp, next_timestamp)`. A
   value of 2 or more at any point means a double booking exists somewhere in that
   interval.

## Solution

### Approach: Difference Array with Sweep Line

We maintain a sparse difference array (`timeline` dictionary). For each booking attempt:

1. Tentatively apply the delta for the new event.
2. Sweep through all timestamps in sorted order, accumulating the running sum.
3. If the running sum reaches 2 at any point → double booking detected → roll back
   and return `False`.
4. Otherwise, keep the booking and return `True`.

### Algorithm Steps:

1. **Tentative insertion**:
   ```
   timeline[start] += 1
   timeline[end]   -= 1
   ```

2. **Sweep**:
   ```
   running_sum = 0
   for each timestamp in sorted(timeline):
       running_sum += timeline[timestamp]
       if running_sum >= 2:
           roll back and return False
   return True
   ```

### Example Walkthrough:

**Try `book(10, 20)`** → tentative: `timeline = {10: +1, 20: -1}`
```
Sweep: ts=10 → sum=1, ts=20 → sum=0   (max=1 < 2) → True ✓
```
Timeline committed: `{10: +1, 20: -1}`

**Try `book(15, 25)`** → tentative: `{10: +1, 15: +1, 20: -1, 25: -1}`
```
Sweep: 10→1, 15→2 ← DOUBLE BOOKING!   → roll back → False ✗
```
Timeline reverts to `{10: +1, 20: -1}`.

**Try `book(20, 30)`** → tentative: `{10: +1, 20: 0, 30: -1}`
```
After adding: timeline[20] was -1, now -1+(-1)=-2? No:
  timeline[20] -= 1 → -1 - 1 = -2? Actually the new event starts at 20, not ends.
  timeline[start=20] += 1 → -1 + 1 = 0
  timeline[end=30]   -= 1 → 30: -1
  So: {10: +1, 20: 0, 30: -1}
Sweep: 10→1, 20→1, 30→0  (max=1 < 2) → True ✓
```
`book(20, 30)` is accepted because `[10, 20)` ends strictly before `[20, 30)` starts.
The value at timestamp 20 nets to 0 (one booking ends, one begins), so the peak stays at 1.

### Code Explanation:

```python
from collections import defaultdict

class MyCalendar:

    def __init__(self):
        self.timeline = defaultdict(int)   # sparse difference array
    
    def book(self, start: int, end: int) -> bool:
        # Step 1: tentatively apply deltas for the new booking
        self.timeline[start] += 1
        self.timeline[end] -= 1

        # Step 2: sweep through sorted timestamps to find peak concurrency
        stack = 0
        for timestamp in sorted(self.timeline):
            stack += self.timeline[timestamp]
            
            if stack >= 2:
                # Step 3: double booking detected → roll back and reject
                self.timeline[start] -= 1
                self.timeline[end] += 1
                return False
        
        # Step 4: no double booking → booking is accepted
        return True
```

### Complexity Analysis:

- **Time Complexity**: O(n²) per call, O(n³) overall
  - `sorted(self.timeline)` costs O(n log n) where n is the number of distinct
    timestamps (at most 2k after k calls).
  - With up to 1000 calls, each scan is O(k log k), giving O(k² log k) total.
  - Within the given constraints (≤1000 calls) this is perfectly acceptable.

- **Space Complexity**: O(n)
  - The `timeline` dictionary holds at most 2n entries after n bookings.

### Key Takeaways:

1. **Difference array on a sparse timeline**: Avoids iterating over all 10^9 possible
   moments by only tracking timestamps where the booking count changes.
2. **Tentative commit + rollback**: A clean pattern for validating a change before
   making it permanent — apply it, check invariants, undo if violated.
3. **Sweep line generalization**: This same technique extends naturally to "no k-tuple
   booking" problems by changing the threshold from 2 to k (see My Calendar II for
   the triple-booking variant).

# Tags

`Segment Tree` `Ordered Set` `Sweep Line` `Difference Array`


````

## Observations

## Solution

# Tags

