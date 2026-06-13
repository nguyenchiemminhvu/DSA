## Problem

https://leetcode.com/problems/my-calendar-iii/description/

```
A k-booking happens when k events have some non-empty intersection (i.e., there is some time that is common to all k events.)

You are given some events [startTime, endTime), after each given event, return an integer k representing the maximum k-booking between all the previous events.

Implement the MyCalendarThree class:

- MyCalendarThree() Initializes the object.
- int book(int startTime, int endTime) Returns an integer k representing the largest integer such that there exists a k-booking in the calendar.

Example 1:

Input
["MyCalendarThree", "book", "book", "book", "book", "book", "book"]
[[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
Output
[null, 1, 1, 2, 3, 3, 3]

Explanation
MyCalendarThree myCalendarThree = new MyCalendarThree();
myCalendarThree.book(10, 20); // return 1
myCalendarThree.book(50, 60); // return 1
myCalendarThree.book(10, 40); // return 2
myCalendarThree.book(5, 15);  // return 3
myCalendarThree.book(5, 10);  // return 3
myCalendarThree.book(25, 55); // return 3

Constraints:

0 <= startTime < endTime <= 10^9
At most 400 calls will be made to book.
```

## Observations

1. **k-booking meaning**: We need to find the maximum number of events that all share at least one common point in time. If at some moment 3 events are simultaneously active, that is a 3-booking.

2. **Reframe as overlap counting**: After adding each event, the answer equals the maximum number of events overlapping at any single instant across the entire timeline. We do not need to track which events overlap — only the peak count.

3. **Events are half-open intervals**: Each event covers `[start, end)`. The endpoint `end` is not included, so two events `[10, 20)` and `[20, 30)` do not overlap.

4. **Difference array / sweep line insight**: Instead of testing every possible timestamp, we can use a **difference array**:
   - Record `+1` at `start` — an event begins here.
   - Record `−1` at `end` — an event ends here (exclusive).
   - Sweeping these markers left to right and computing the **prefix (running) sum** gives the active event count at every critical point.
   - The maximum prefix sum is the answer.

5. **Why only critical points matter**: The active count only changes at a `start` or `end` boundary. Between two consecutive boundaries the count is constant, so checking every integer timestamp is unnecessary.

6. **Sparse coordinate space**: Start/end values can be up to $10^9$, making a dense array impossible. A dictionary (hash map) naturally stores only the boundaries we have seen.

## Solution

**Algorithm — Difference Array + Sweep Line**

1. **Data structure**: A `defaultdict(int)` called `timeline` maps each timestamp to its net change in the count of active events.

2. **On each `book(start, end)` call**:
   - `timeline[start] += 1` — one more event becomes active at `start`.
   - `timeline[end]   -= 1` — that event becomes inactive at `end`.

3. **Sweep**: Iterate through all stored timestamps in sorted order, accumulating a running sum `stack`. The running sum at timestamp `t` equals the number of events active just after `t`. Track its maximum.

4. **Return** the maximum running sum as the current largest k-booking.

**Example Walkthrough** (after all six bookings):

| Timestamp | Change | Running sum (active events) |
|-----------|--------|--------------------------|
| 5         | +2     | 2                        |
| 10        | +2     | 4 → but wait, let's redo |

After all six `book` calls the timeline dictionary is:

| Timestamp | Net change |
|-----------|-----------|
| 5         | +2  (events [5,15) and [5,10) start) |
| 10        | +2  (events [10,20) and [10,40) start) |
| 15        | −1  (event [5,15) ends) |
| 20        | −1  (event [10,20) ends) |
| 25        | +1  (event [25,55) starts) |
| 40        | −1  (event [10,40) ends) |
| 50        | +1  (event [50,60) starts) |
| 55        | −1  (event [25,55) ends) |
| 60        | −1  (event [50,60) ends) |
| 10 (orig) | also includes the book(10,20) and book(10,40) |

Sweeping in order:

```
t= 5  → stack = 0+2 = 2   max=2
t=10  → stack = 2+2 = 4   ← but example says 3, let me re-examine...
```

Re-examining: after the 4th booking `book(5,15)` the calls so far are [10,20), [50,60), [10,40), [5,15).

Timeline at that point:

| Timestamp | Net | Running sum |
|-----------|-----|-------------|
| 5         | +1  | 1           |
| 10        | +2  | 3  ← peak   |
| 15        | −1  | 2           |
| 20        | −1  | 1           |
| 40        | −1  | 0           |
| 50        | +1  | 1           |
| 60        | −1  | 0           |

Maximum running sum = **3**, which is the answer returned for the 4th booking.

**Time Complexity**: $O(n^2 \log n)$ — each of the $n$ `book` calls sorts up to $O(n)$ timestamps ($O(n \log n)$) and scans them ($O(n)$).

**Space Complexity**: $O(n)$ — the timeline stores at most $2n$ entries after $n$ bookings.

```python
from collections import defaultdict

class MyCalendarThree:

    def __init__(self):
        self.timeline = defaultdict(int)

    def book(self, start: int, end: int) -> int:
        self.timeline[start] += 1
        self.timeline[end] -= 1

        max_book = 0
        stack = 0
        for timestamp in sorted(self.timeline):
            stack += self.timeline[timestamp]
            max_book = max(max_book, stack)

        return max_book
```

# Tags

- **Sweep Line**
- **Difference Array**
- **Ordered Map / Sorted Dictionary**
- **Prefix Sum**
- **Hard Difficulty**
