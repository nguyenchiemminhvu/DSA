## Problem

https://leetcode.com/problems/the-latest-time-to-catch-a-bus/description/

You are given:
- `buses`: 0-indexed integer array of length n, where `buses[i]` is the departure time of the ith bus
- `passengers`: 0-indexed integer array of length m, where `passengers[j]` is the arrival time of the jth passenger
- `capacity`: maximum number of passengers that can board each bus
- All bus departure times and passenger arrival times are unique

Rules:
- A passenger arriving at time y can board a bus departing at time x if y ≤ x and the bus is not full
- Passengers board in order of earliest arrival time
- You cannot arrive at the same time as another passenger
- Return the latest time you can arrive to catch a bus

## Observations

1. **Greedy Strategy**: Passengers board the earliest available bus they can catch. We need to simulate this process to understand the capacity utilization of each bus.

2. **Sorting is Essential**: Both arrays must be sorted to track which passengers board which bus. After sorting, we can use a pointer to traverse passengers in order.

3. **Key Insight for Answer**: 
   - If the last bus has available capacity after all passengers board, we can arrive at the last bus's departure time
   - If the last bus is at full capacity, we must arrive one minute before the last passenger boarding it
   - We cannot arrive at the exact time of any existing passenger, so we decrement the time until it's available

4. **Simulation**: Iterate through each bus in order. For each bus, board up to `capacity` passengers whose arrival time is ≤ the bus departure time.

## Solution

```python
class Solution:
    def latestTimeCatchTheBus(self, buses: List[int], passengers: List[int], capacity: int) -> int:
        buses.sort()
        passengers.sort()
        
        # Simulate: track which bus each passenger boards
        ip = 0  # passenger index
        for bus in buses:
            count = 0
            # Board passengers whose arrival <= bus departure, up to capacity
            while ip < m and passengers[ip] <= bus and count < capacity:
                ip += 1
                count += 1
        
        # Determine latest arrival time
        if count < capacity:
            # Last bus has available capacity
            res = buses[-1]
        else:
            # Last bus is full, arrive before the last passenger boarding it
            res = passengers[ip - 1] - 1
        
        # Handle conflicts: cannot arrive same time as any passenger
        s = set(passengers)
        while res in s:
            res -= 1
        
        return res
```

**Algorithm Explanation**:

1. **Sort arrays**: O(n log n + m log m) preprocessing to enable efficient simulation

2. **Simulate bus boarding**:
   - For each bus in chronological order, greedily board passengers with earliest arrival times
   - The pointer `ip` tracks the next passenger to process
   - `count` tracks how many passengers board the current bus

3. **Determine arrival time**:
   - If `count < capacity`: The last bus isn't full, so we can arrive at its departure time (latest possible)
   - If `count == capacity`: The last bus is at full capacity, so we can arrive at most 1 minute before the last passenger (`passengers[ip-1] - 1`)

4. **Conflict resolution**:
   - Check if our arrival time matches any passenger's arrival time
   - If it does, decrement by 1 and check again
   - In worst case, we go back from `passengers[ip-1] - 1` down to at least `passengers[ip-capacity]`

**Time Complexity**: O(n log n + m log m) for sorting + O(n + m) for simulation = O((n+m) log (n+m))

**Space Complexity**: O(m) for the set of passenger arrival times

# Tags
- Greedy
- Simulation
- Binary Search (alternative approach)
- Sorting

