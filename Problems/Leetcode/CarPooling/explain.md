## Problem

https://leetcode.com/problems/car-pooling/description/

```
There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn around and drive west).

You are given the integer capacity and an array trips where trips[i] = [numPassengersi, fromi, toi] indicates that 
the ith trip has numPassengersi passengers and the locations to pick them up and drop them off are fromi and toi 
respectively. The locations are given as the number of kilometers due east from the car's initial location.

Return true if it is possible to pick up and drop off all passengers for all the given trips, or false otherwise.

Example 1:
Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false

Example 2:
Input: trips = [[2,1,5],[3,3,7]], capacity = 5
Output: true

Constraints:
- 1 <= trips.length <= 1000
- trips[i].length == 3
- 1 <= numPassengersi <= 100
- 0 <= fromi < toi <= 1000
- 1 <= capacity <= 10^5
```

## Observations

1. **Timeline-based Problem**: The car travels in one direction (east), so we can model this as events happening along a timeline where each location is a timestamp.

2. **Two Types of Events**: At each location, two types of events can occur:
   - **Pick-up events**: Passengers board the car (increase current passengers)
   - **Drop-off events**: Passengers leave the car (decrease current passengers)

3. **Critical Insight**: We need to track the current number of passengers at each point in the journey. If at any point the current passengers exceed capacity, return false.

4. **Event Processing Order**: 
   - Events should be processed in order of location (ascending)
   - At the same location, drop-offs should be processed before pick-ups (passengers leave before new ones board)

5. **Optimization**: Instead of simulating every kilometer from 0 to 1000, we only need to check locations where events occur (pick-ups or drop-offs).

## Solution

### Approach: Event Timeline (Sweep Line Algorithm)

**Algorithm:**

1. **Build Event Map**: Create a dictionary/map where:
   - Key: location (kilometer mark)
   - Value: `[pick_ups, drop_offs]` - number of passengers boarding and leaving at this location

2. **Process All Trips**: For each trip `[numPassengers, from, to]`:
   - Add `numPassengers` to pick-ups at location `from`
   - Add `numPassengers` to drop-offs at location `to`

3. **Create Sorted Timeline**: Convert the event map into a sorted list of events ordered by location.

4. **Simulate Journey**: Traverse the timeline in order:
   - At each location, first process drop-offs (decrease current passengers)
   - Then process pick-ups (increase current passengers)
   - Check if current passengers exceed capacity
   - If yes, return `False`

5. **Return Result**: If we complete the entire journey without exceeding capacity, return `True`.

**Why Drop-offs Before Pick-ups?**
At the same location, passengers must exit before new passengers can board. This maximizes available capacity and reflects real-world behavior.

### Python Implementation

```python
class Solution:
    def carPooling(self, trips: List[List[int]], cap: int) -> bool:
        # Step 1: Build event map
        events = {}
        for num, start, end in trips:
            if start not in events:
                events[start] = [0, 0]  # [pick_ups, drop_offs]
            if end not in events:
                events[end] = [0, 0]
            events[start][0] += num  # Add pick-ups at start location
            events[end][1] += num     # Add drop-offs at end location
        
        # Step 2: Create sorted timeline
        # Format: (location, pick_ups, drop_offs)
        timeline = sorted([(k, v[0], v[1]) for k, v in events.items()])
        
        # Step 3: Simulate the journey
        cur = 0  # Current number of passengers
        for timestamp, pick, drop in timeline:
            cur -= drop  # Process drop-offs first
            cur += pick  # Then process pick-ups
            if cur > cap:  # Check capacity constraint
                return False
        
        return True
```

### Complexity Analysis

**Time Complexity**: O(n log n)
- Building the events map: O(n) where n = number of trips
- Sorting the timeline: O(m log m) where m = number of unique locations (m ≤ 2n)
- Traversing the timeline: O(m)
- Overall: O(n log n)

**Space Complexity**: O(m)
- Events dictionary: O(m) where m ≤ 2n (at most 2 events per trip)
- Timeline list: O(m)
- Overall: O(n)

### Example Walkthrough

**Example 1**: `trips = [[2,1,5],[3,3,7]]`, `capacity = 4`

Events map:
- Location 1: [2, 0] (2 pick-ups)
- Location 3: [3, 0] (3 pick-ups)
- Location 5: [0, 2] (2 drop-offs)
- Location 7: [0, 3] (3 drop-offs)

Timeline: `[(1,2,0), (3,3,0), (5,0,2), (7,0,3)]`

Simulation:
- Location 1: cur = 0 - 0 + 2 = 2 ✓
- Location 3: cur = 2 - 0 + 3 = 5 ✗ (exceeds capacity 4)

**Output**: `false`

**Example 2**: `trips = [[2,1,5],[3,3,7]]`, `capacity = 5`

Same events, but capacity = 5

Simulation:
- Location 1: cur = 0 - 0 + 2 = 2 ✓
- Location 3: cur = 2 - 0 + 3 = 5 ✓
- Location 5: cur = 5 - 2 + 0 = 3 ✓
- Location 7: cur = 3 - 3 + 0 = 0 ✓

**Output**: `true`

### Alternative Approaches

1. **Difference Array** (similar concept):
   - Use an array of size 1001 (max location + 1)
   - Mark changes at each location
   - Compute prefix sum to get current passengers
   - Time: O(n + max_location), Space: O(max_location)

2. **Heap/Priority Queue**:
   - Use min-heap to track drop-off events
   - Process pick-ups in order
   - Time: O(n log n), Space: O(n)

# Tags

`Array` `Sorting` `Heap (Priority Queue)` `Simulation` `Prefix Sum` `Sweep Line` `Greedy`

