## Problem

https://leetcode.com/problems/determine-if-two-events-have-conflict/description/

You are given two arrays of strings that represent two inclusive events that happened on the same day, `event1` and `event2`, where:

- `event1 = [startTime1, endTime1]` and
- `event2 = [startTime2, endTime2]`

Event times are valid 24 hours format in the form of `HH:MM`.

A conflict happens when two events have some non-empty intersection (i.e., some moment is common to both events).

Return `true` if there is a conflict between two events. Otherwise, return `false`.

### Example 1:
```
Input: event1 = ["01:15","02:00"], event2 = ["02:00","03:00"]
Output: true
Explanation: The two events intersect at time 2:00.
```

### Example 2:
```
Input: event1 = ["01:00","02:00"], event2 = ["01:20","03:00"]
Output: true
Explanation: The two events intersect starting from 01:20 to 02:00.
```

### Example 3:
```
Input: event1 = ["10:00","11:00"], event2 = ["14:00","15:00"]
Output: false
Explanation: The two events do not intersect.
```

### Constraints:
- `event1.length == event2.length == 2`
- `event1[i].length == event2[i].length == 5`
- `startTime1 <= endTime1`
- `startTime2 <= endTime2`
- All the event times follow the `HH:MM` format

## Observations

1. **Time Representation**: Times are given as strings in "HH:MM" format. To compare them easily, we can convert them to minutes since midnight.

2. **Interval Overlap Problem**: This is essentially an interval overlap problem. Two intervals `[a, b]` and `[c, d]` overlap if and only if:
   - `max(a, c) <= min(b, d)`
   
3. **Sorted Intervals Approach**: If we sort the intervals by their start times, the first interval starts earlier (or at the same time). For overlap to exist:
   - The second interval must start before or at the time when the first interval ends
   - Mathematically: `intervals[1][0] <= intervals[0][1]`

4. **Edge Cases**:
   - Events that touch at exactly one point (like "02:00" and "02:00") are considered conflicting
   - Events completely contained within another event
   - Events that don't overlap at all

5. **String Comparison Shortcut**: Since times are in "HH:MM" format, they can be compared lexicographically! "01:20" < "02:00" works correctly.

## Solution

### Approach: Convert to Minutes + Sorted Interval Check

**Algorithm Steps:**

1. **Convert Time to Minutes**:
   - Create a helper function `to_minute(s)` that converts "HH:MM" to total minutes since midnight
   - Extract hours and minutes from the string
   - Formula: `total_minutes = hours * 60 + minutes`

2. **Create Intervals**:
   - Convert both events to minute-based intervals
   - `event1` becomes `[to_minute(event1[0]), to_minute(event1[1])]`
   - `event2` becomes `[to_minute(event2[0]), to_minute(event2[1])]`

3. **Sort by Start Time**:
   - Sort the intervals by their start times (first element)
   - After sorting, `intervals[0]` is the interval that starts first

4. **Check for Overlap**:
   - If the second interval starts before or when the first interval ends, they overlap
   - Return `intervals[1][0] <= intervals[0][1]`

**Visual Example:**
```
Event 1: ["01:00", "02:00"] → [60, 120]
Event 2: ["01:20", "03:00"] → [80, 180]

After sorting by start time:
intervals[0] = [60, 120]   (starts at 01:00, ends at 02:00)
intervals[1] = [80, 180]   (starts at 01:20, ends at 03:00)

Check: 80 <= 120? YES → They overlap!
```

**Non-overlapping Example:**
```
Event 1: ["10:00", "11:00"] → [600, 660]
Event 2: ["14:00", "15:00"] → [840, 900]

After sorting:
intervals[0] = [600, 660]
intervals[1] = [840, 900]

Check: 840 <= 660? NO → No overlap!
```

### Complexity Analysis:

- **Time Complexity**: O(1)
  - Converting times to minutes: O(1) for each time
  - Sorting 2 intervals: O(1) (constant size)
  - Comparison: O(1)

- **Space Complexity**: O(1)
  - Only storing two intervals with fixed size

### Alternative Approaches:

**1. String Comparison (Simpler):**
```python
def haveConflict(self, event1: List[str], event2: List[str]) -> bool:
    return not (event1[1] < event2[0] or event2[1] < event1[0])
```
This works because times in "HH:MM" format can be compared lexicographically!

**2. Direct Max/Min Approach:**
```python
def haveConflict(self, event1: List[str], event2: List[str]) -> bool:
    return max(event1[0], event2[0]) <= min(event1[1], event2[1])
```
This directly implements the overlap condition without sorting.

# Tags

`Array` `String` `Intervals` `Sorting`

