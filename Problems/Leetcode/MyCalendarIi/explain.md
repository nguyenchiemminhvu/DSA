## Problem

https://leetcode.com/problems/my-calendar-ii/description/

```
You are implementing a program to use as your calendar. We can add a new event
if adding the event will not cause a triple booking.

A triple booking happens when three events have some non-empty intersection
(i.e., some moment is common to all the three events).

The event can be represented as a pair of integers startTime and endTime that
represents a booking on the half-open interval [startTime, endTime).

Implement the MyCalendarTwo class:
- MyCalendarTwo() Initializes the calendar object.
- boolean book(int startTime, int endTime) Returns true if the event can be
  added to the calendar successfully without causing a triple booking. Otherwise,
  return false and do not add the event to the calendar.

Example 1:
Input
["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]
[[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
Output
[null, true, true, true, false, true, true]

Explanation
MyCalendarTwo myCalendarTwo = new MyCalendarTwo();
myCalendarTwo.book(10, 20); // return True, The event can be booked.
myCalendarTwo.book(50, 60); // return True, The event can be booked.
myCalendarTwo.book(10, 40); // return True, The event can be double booked.
myCalendarTwo.book(5, 15);  // return False, The event cannot be booked, because
                             // it would result in a triple booking.
myCalendarTwo.book(5, 10);  // return True, The event can be booked, as it does
                             // not use time 10 which is already double booked.
myCalendarTwo.book(25, 55); // return True, The event can be booked, as the time
                             // in [25, 40) will be double booked with the third
                             // event, the time [40, 50) will be single booked,
                             // and the time [50, 55) will be double booked with
                             // the second event.

Constraints:
- 0 <= startTime < endTime <= 10^9
- At most 1000 calls will be made to book.
```

## Observations

1. **Half-open intervals**: Each booking covers `[start, end)`. A moment `x` is covered
   by a booking if `start <= x < end`. The problem asks us to prevent any moment from
   being covered by 3 or more overlapping bookings simultaneously.

2. **Difference Array / Sweep Line Technique**: Instead of checking every possible
   moment (which can be up to 10^9), we can model the timeline as a sparse map of
   **change events**:
   - When a booking `[start, end)` is added, the "active booking count" increases by 1
     at `start` and decreases by 1 at `end`.
   - By sweeping through all recorded timestamps in sorted order and accumulating these
     deltas, we can compute the maximum concurrent bookings at any point in time.

3. **Sparse representation**: Since at most 1000 calls are made, there are at most
   2000 distinct timestamps. A `defaultdict(int)` efficiently stores only the relevant
   points without allocating memory for the whole `[0, 10^9]` range.

4. **Validation before committing**: To check whether a new event `[start, end)` causes
   a triple booking, we **tentatively add** the deltas (`timeline[start] += 1`,
   `timeline[end] -= 1`), run the sweep, and if the running sum ever reaches 3, we
   **roll back** the changes and return `False`. If no violation is found, the booking
   stands and we return `True`.

5. **Why the sweep works**: The running prefix sum at any sorted timestamp equals the
   exact number of active bookings in the interval `[timestamp, next_timestamp)`. A
   value of 3 or more at any point means a triple booking exists somewhere in that
   interval.

## Solution

### Approach: Difference Array with Sweep Line

We maintain a sparse difference array (`timeline` dictionary). For each booking attempt:

1. Tentatively apply the delta for the new event.
2. Sweep through all timestamps in sorted order, accumulating the running sum.
3. If the running sum reaches 3 at any point → triple booking detected → roll back
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
       if running_sum >= 3:
           roll back and return False
   return True
   ```

### Example Walkthrough:

**After `book(10, 20)`** → `timeline = {10: +1, 20: -1}`
```
Sweep: ts=10 → sum=1, ts=20 → sum=0   (max=1 < 3) → True ✓
```

**After `book(50, 60)`** → `timeline = {10:+1, 20:-1, 50:+1, 60:-1}`
```
Sweep: 10→1, 20→0, 50→1, 60→0        (max=1 < 3) → True ✓
```

**After `book(10, 40)`** → `timeline = {10:+2, 20:-1, 40:-1, 50:+1, 60:-1}`
```
Sweep: 10→2, 20→1, 40→0, 50→1, 60→0  (max=2 < 3) → True ✓
```

**Try `book(5, 15)`** → tentative: `{5:+1, 10:+2, 15:-1, 20:-1, 40:-1, 50:+1, 60:-1}`
```
Sweep: 5→1, 10→3 ← TRIPLE BOOKING!   → roll back → False ✗
```
Timeline reverts to previous state.

**Try `book(5, 10)`** → tentative: `{5:+1, 10:+2, 20:-1, 40:-1, 50:+1, 60:-1}`
```
Sweep: 5→1, 10→3 ← wait, does 5→10 overlap?
Actually timeline[10] is still +2 (from bookings [10,20) and [10,40)).
5→1, 10→1+2=3? Let's recount:
  After book(5,10): timeline[5]+=1 → 5:+1, timeline[10]-=1 → 10:+2-1=+1
  So: {5:+1, 10:+1, 20:-1, 40:-1, 50:+1, 60:-1}
Sweep: 5→1, 10→2, 20→1, 40→0, 50→1, 60→0  (max=2 < 3) → True ✓
```
Note: `book(5,10)` ends exactly at 10, so the interval `[5,10)` doesn't overlap with
the double-booked `[10,20) ∩ [10,40)` segment.

**Try `book(25, 55)`** → tentative adds `25:+1, 55:-1`
```
Full timeline: {5:+1, 10:+1, 20:-1, 25:+1, 40:-1, 50:+1, 55:-1, 60:-1}
Sweep:
  5  → 1
  10 → 2
  20 → 1
  25 → 2
  40 → 1
  50 → 2
  55 → 1
  60 → 0
  (max=2 < 3) → True ✓
```

### Code Explanation:

```python
from collections import defaultdict

class MyCalendarTwo:

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
            
            if stack >= 3:
                # Step 3: triple booking detected → roll back and reject
                self.timeline[start] -= 1
                self.timeline[end] += 1
                return False
        
        # Step 4: no triple booking → booking is accepted
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
   booking" problems by changing the threshold from 3 to k.

# Tags

`Segment Tree` `Ordered Set` `Sweep Line` `Difference Array`

