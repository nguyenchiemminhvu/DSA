# Two Best Non-Overlapping Events

## Problem

https://leetcode.com/problems/two-best-non-overlapping-events/description/

You are given a 0-indexed 2D integer array of events where `events[i] = [startTimei, endTimei, valuei]`. The ith event starts at `startTimei` and ends at `endTimei`, and if you attend this event, you will receive a value of `valuei`.

You can choose **at most two non-overlapping events** to attend such that the sum of their values is maximized.

Return this maximum sum.

**Note:** The start time and end time is inclusive. You cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time `t`, the next event must start at or after `t + 1`.

### Examples

**Example 1:**
```
Input: events = [[1,3,2],[4,5,2],[2,4,3]]
Output: 4
Explanation: Choose events 0 and 1 (times [1,3] and [4,5]) for a sum of 2 + 2 = 4.
```

**Example 2:**
```
Input: events = [[1,3,2],[4,5,2],[1,5,5]]
Output: 5
Explanation: Choose event 2 for a sum of 5 (better than any two non-overlapping events).
```

**Example 3:**
```
Input: events = [[1,5,3],[1,5,1],[6,6,5]]
Output: 8
Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.
```

### Constraints
- `2 <= events.length <= 10^5`
- `events[i].length == 3`
- `1 <= startTimei <= endTimei <= 10^9`
- `1 <= valuei <= 10^6`

---

## Observations

1. **At Most Two Events**: We need to select at most 2 non-overlapping events (could be 0, 1, or 2 events).

2. **Non-Overlapping Constraint**: Two events are non-overlapping if one ends before the other starts. Specifically, if event A ends at time `t`, event B must start at time `t + 1` or later.

3. **Timeline-Based Approach**: Instead of checking every pair of events (O(n²)), we can process events chronologically using their start and end times.

4. **Event Boundaries Matter**: We care about two types of time points:
   - **Start times**: When an event begins (potential to add to current max)
   - **End times**: When an event ends (update max value seen so far)

5. **Greedy Strategy**: As we move through time:
   - Track the maximum value of any event that has already ended
   - When we encounter a new event starting, we can pair it with the best ended event

---

## Solution

### Approach: Sweep Line Algorithm

#### Core Idea

Transform the problem into a timeline where we process all event boundaries (starts and ends) in chronological order. At each point:
- When an event **starts**: Consider pairing it with the best event that has already ended
- When an event **ends**: Update the maximum value available for future pairings

#### Algorithm Steps

1. **Create Timeline Points**:
   - For each event `[start, end, value]`:
     - Add `[start, 1, value]` (type 1 = event starting)
     - Add `[end + 1, 0, value]` (type 0 = event ending, use `end + 1` because next event must start after this one ends)

2. **Sort Timeline**: Sort all points by time. If times are equal, process end events (type 0) before start events (type 1) to ensure we don't miss valid pairings.

3. **Process Timeline**:
   - Maintain `cur_max`: the maximum value of any event that has completely ended
   - Maintain `res`: the maximum sum achieved
   - For each time point:
     - **If it's a start** (type 1): `res = max(res, value + cur_max)` (pair this event with best ended event)
     - **If it's an end** (type 0): `cur_max = max(cur_max, value)` (update best ended event)

#### Why This Works

- By processing events chronologically, when we encounter a starting event, all events that have ended are in `cur_max`
- The `end + 1` trick ensures proper non-overlapping: an event ending at time `t` becomes available at time `t + 1`
- We automatically handle all three cases: selecting 0, 1, or 2 events

#### Implementation

```python
class Solution:
    def maxTwoEvents(self, events: List[List[int]]) -> int:
        times = []
        
        # Create timeline points
        for e in events:
            times.append([e[0], 1, e[2]])      # Start: [start_time, type=1, value]
            times.append([e[1] + 1, 0, e[2]])  # End: [end_time+1, type=0, value]
        
        # Sort by time (and implicitly by type if times are equal)
        times.sort()
        
        res = 0       # Maximum sum achieved
        cur_max = 0   # Maximum value of events that have ended
        
        for t in times:
            if t[1] == 1:  # Event starting
                # Try pairing this event with the best ended event
                res = max(res, t[2] + cur_max)
            else:  # Event ending (t[1] == 0)
                # Update the best value available for future pairings
                cur_max = max(cur_max, t[2])
        
        return res
```

#### Complexity Analysis

**Time Complexity: O(n log n)**
- Creating timeline points: O(n)
- Sorting timeline points: O(n log n) where n is the number of events
- Processing timeline points: O(n)
- Overall: O(n log n)

**Space Complexity: O(n)**
- Storing 2n timeline points in the `times` array

#### Example Walkthrough

Let's trace through Example 1: `events = [[1,3,2],[4,5,2],[2,4,3]]`

**Step 1: Create timeline**
```
Event [1,3,2] → [1, 1, 2] and [4, 0, 2]
Event [4,5,2] → [4, 1, 2] and [6, 0, 2]
Event [2,4,3] → [2, 1, 3] and [5, 0, 3]
```

**Step 2: Sort timeline**
```
[1, 1, 2]   # Event 1 starts
[2, 1, 3]   # Event 3 starts
[4, 0, 2]   # Event 1 ends (available at time 4)
[4, 1, 2]   # Event 2 starts
[5, 0, 3]   # Event 3 ends (available at time 5)
[6, 0, 2]   # Event 2 ends (available at time 6)
```

**Step 3: Process timeline**
```
Time [1, 1, 2]: Start → res = max(0, 2 + 0) = 2
Time [2, 1, 3]: Start → res = max(2, 3 + 0) = 3
Time [4, 0, 2]: End   → cur_max = max(0, 2) = 2
Time [4, 1, 2]: Start → res = max(3, 2 + 2) = 4  ← This pairs events 1 and 2!
Time [5, 0, 3]: End   → cur_max = max(2, 3) = 3
Time [6, 0, 2]: End   → cur_max = max(3, 2) = 3
```

**Result: 4**

---

### Alternative Approaches

**1. Dynamic Programming with Sorting**
- Sort events by end time
- For each event, use binary search to find the latest non-overlapping event
- DP[i] = max value using events up to index i
- Time: O(n log n), Space: O(n)

**2. Brute Force**
- Check all pairs of events for non-overlapping
- Time: O(n²), Space: O(1)
- Not suitable for n = 10^5

---

## Key Takeaways

1. **Sweep line algorithm** is powerful for interval-based problems
2. Converting events to timeline points simplifies chronological processing
3. The `end + 1` trick elegantly handles the inclusive end time constraint
4. Greedy tracking of `cur_max` avoids checking all previous events
5. This approach naturally handles edge cases (selecting 0, 1, or 2 events)

# Tags

`Array` `Sorting` `Greedy` `Sweep Line` `Intervals` `Two Pointers`

