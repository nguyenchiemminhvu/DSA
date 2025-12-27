## Problem

https://leetcode.com/problems/meeting-rooms-iii/description/

You are given an integer `n` representing `n` rooms numbered from `0` to `n - 1`.

You are given a 2D integer array `meetings` where `meetings[i] = [start_i, end_i]` means that a meeting will be held during the half-closed time interval `[start_i, end_i)`. All values of `start_i` are unique.

**Meeting Allocation Rules:**
1. Each meeting will take place in the unused room with the **lowest number**
2. If no rooms are available, the meeting is **delayed** until a room becomes free (maintaining the same duration)
3. When a room becomes free, meetings with **earlier original start times** are prioritized

**Goal:** Return the room number that held the most meetings. If there's a tie, return the room with the lowest number.

## Observations

1. **Priority Queue Management**: We need to track both free and busy rooms efficiently
   - Free rooms: min-heap by room number (to get lowest numbered room)
   - Busy rooms: min-heap by end time, then room number (to know when rooms become free)

2. **Meeting Processing Order**: Meetings must be processed by their original start time (already sorted input)

3. **Room Release Timing**: Before assigning each meeting, we must:
   - Release all rooms that finished by current meeting's start time
   - Move them from busy_rooms → free_rooms

4. **Two Scenarios for Assignment**:
   - **Free room available**: Assign to lowest numbered free room, meeting ends at `start + duration`
   - **No free rooms**: Take the room that finishes earliest, meeting ends at `earliest_end + duration`

5. **Counting**: Track meetings per room to find the room with maximum meetings

6. **Edge Case**: The delayed meeting maintains its original duration, not absolute end time

## Solution

**Algorithm Flow:**

```
1. Initialize:
   - count: dictionary to track meetings per room
   - free_rooms: min-heap with all rooms [0, n-1]
   - busy_rooms: min-heap (end_time, room_number)
   - meetings: sort by start time (already unique)

2. For each meeting (start, end):
   a. Release rooms: while busy_rooms.top.end_time <= start:
      - Move room from busy_rooms to free_rooms
   
   b. Assign meeting:
      - If free_rooms available:
        * room = free_rooms.pop()
        * busy_rooms.push((end, room))
      - Else (all busy):
        * (earliest_end, room) = busy_rooms.pop()
        * duration = end - start
        * busy_rooms.push((earliest_end + duration, room))
   
   c. count[room] += 1

3. Return room with max count (ties → lowest number)
```

**Time Complexity:** O(m log m + m log n) where m = meetings, n = rooms
- Sorting meetings: O(m log m) if not sorted
- Each meeting: O(log n) heap operations
- Overall: O(m log n)

**Space Complexity:** O(n + m)
- Heaps store at most n rooms
- Queue stores m meetings
- Count dictionary stores at most n entries

**Key Implementation Details:**

```python
# Custom min_heap wrapper for cleaner code
class min_heap:
    def push(obj):    # heapq.heappush
    def get():        # peek at top
    def pop():        # heapq.heappop
    def __bool__():   # check if empty

# Main logic:
busy_rooms.push((end, room))  # Tuples compare first by end time
free_rooms.push(room)          # Just room number

# Delayed meeting calculation:
busy_end + duration  # NOT just end time!
```

**Example Walkthrough (n=2, meetings=[[0,10],[1,5],[2,7],[3,4]]):**

```
Time 0: Meeting [0,10)
  - Free: [0,1] → Assign room 0
  - Busy: [(10,0)]
  - Count: {0:1}

Time 1: Meeting [1,5)
  - Free: [1] → Assign room 1
  - Busy: [(10,0), (5,1)]
  - Count: {0:1, 1:1}

Time 2: Meeting [2,7) duration=5
  - Free: [] → Delayed!
  - Busy: [(5,1), (10,0)] → Room 1 finishes earliest
  - Assign room 1: ends at 5+5=10
  - Busy: [(10,0), (10,1)]
  - Count: {0:1, 1:2}

Time 3: Meeting [3,4) duration=1
  - Free: [] → Delayed!
  - Busy: [(10,0), (10,1)] → Room 0 finishes first (tie by room number)
  - Assign room 0: ends at 10+1=11
  - Busy: [(10,1), (11,0)]
  - Count: {0:2, 1:2}

Result: Rooms 0 and 1 both held 2 meetings → return 0 (lowest)
```

# Tags

