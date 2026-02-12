## Problem

https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/description/

```
There is a party where n friends numbered from 0 to n - 1 are attending. There is an infinite number of chairs in this party that are numbered from 0 to infinity. When a friend arrives at the party, they sit on the unoccupied chair with the smallest number.

For example, if chairs 0, 1, and 5 are occupied when a friend comes, they will sit on chair number 2.
When a friend leaves the party, their chair becomes unoccupied at the moment they leave. If another friend arrives at that same moment, they can sit in that chair.

You are given a 0-indexed 2D integer array times where times[i] = [arrivali, leavingi], indicating the arrival and leaving times of the ith friend respectively, and an integer targetFriend. All arrival times are distinct.

Return the chair number that the friend numbered targetFriend will sit on.

Example 1:
Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
Output: 1
Explanation: 
- Friend 0 arrives at time 1 and sits on chair 0.
- Friend 1 arrives at time 2 and sits on chair 1.
- Friend 1 leaves at time 3 and chair 1 becomes empty.
- Friend 0 leaves at time 4 and chair 0 becomes empty.
- Friend 2 arrives at time 4 and sits on chair 0.
Since friend 1 sat on chair 1, we return 1.

Example 2:
Input: times = [[3,10],[1,5],[2,6]], targetFriend = 0
Output: 2
Explanation: 
- Friend 1 arrives at time 1 and sits on chair 0.
- Friend 2 arrives at time 2 and sits on chair 1.
- Friend 0 arrives at time 3 and sits on chair 2.
- Friend 1 leaves at time 5 and chair 0 becomes empty.
- Friend 2 leaves at time 6 and chair 1 becomes empty.
- Friend 0 leaves at time 10 and chair 2 becomes empty.
Since friend 0 sat on chair 2, we return 2.

Constraints:
- n == times.length
- 2 <= n <= 10^4
- times[i].length == 2
- 1 <= arrivali < leavingi <= 10^5
- 0 <= targetFriend <= n - 1
- Each arrivali time is distinct.
```

## Observations

1. **Event-based simulation**: We need to simulate the party by processing arrival and leaving events in chronological order.

2. **Chair allocation strategy**: Always assign the smallest available chair number to arriving friends.

3. **Chair recycling**: When a friend leaves, their chair becomes available for future arrivals.

4. **Edge case handling**: When a friend leaves and another arrives at the same moment, the leaving event should be processed first (so the chair becomes available for the arriving friend).

5. **Key insight**: We don't need to simulate until all events are done - we can return immediately when the target friend arrives.

## Solution

### Approach: Event-based Simulation with Min-Heap

**Core Strategy:**
- Use a min-heap to track available chairs (always gives us the smallest available chair)
- Create events for both arrivals and departures
- Process events chronologically
- Track which chair each friend is sitting on

**Implementation Details:**

```python
import heapq

class Solution:
    def smallestChair(self, times: List[List[int]], target: int) -> int:
        # Initialize heap with all chair numbers (0 to n-1)
        pq = [i for i in range(len(times))]
        heapq.heapify(pq)

        # Create events: (timestamp, event_type, friend_id)
        events = []
        for i, (arrive, leave) in enumerate(times):
            events.append((arrive, 1, i))  # 1 = arrival event
            events.append((leave, 0, i))   # 0 = departure event
        
        # Sort by timestamp, then by event type (departures before arrivals)
        events.sort(key=lambda x: (x[0], x[1]))

        # Map friend_id -> chair_id
        map_seat = {}
        
        for timestamp, state, i in events:
            if state == 1:  # Arrival event
                seat = heapq.heappop(pq)  # Get smallest available chair
                if i == target:
                    return seat
                map_seat[i] = seat
            else:  # Departure event
                seat = map_seat[i]
                heapq.heappush(pq, seat)  # Return chair to available pool
        
        return -1
```

**Algorithm Complexity:**
- **Time Complexity**: O(n log n)
  - Creating events: O(n)
  - Sorting events: O(n log n)
  - Processing events with heap operations: O(n log n)
- **Space Complexity**: O(n)
  - Heap stores up to n chairs
  - Events list stores 2n events
  - Map stores up to n mappings

**Key Design Decisions:**

1. **Event ordering**: Sort by `(timestamp, event_type)` where departure (0) comes before arrival (1). This ensures that when someone leaves at time T and someone arrives at time T, the chair becomes available first.

2. **Min-heap for chairs**: Guarantees O(log n) time to get the smallest available chair and to return a chair to the pool.

3. **Early termination**: We can return immediately when the target friend gets their chair, avoiding unnecessary processing.

4. **Friend-to-chair mapping**: Essential for knowing which chair to free when a friend leaves.

# Tags
`heap`, `priority-queue`, `simulation`, `event-processing`, `greedy`, `sorting`

