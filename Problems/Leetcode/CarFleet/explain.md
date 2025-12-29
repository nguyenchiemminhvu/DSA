## Problem

https://leetcode.com/problems/car-fleet/description/

There are `n` cars at given miles away from the starting mile 0, traveling to reach the mile `target`.

You are given two integer arrays `position` and `speed`, both of length `n`, where `position[i]` is the starting mile of the ith car and `speed[i]` is the speed of the ith car in miles per hour.

A car **cannot pass** another car, but it can catch up and then travel next to it at the speed of the slower car.

A **car fleet** is a single car or a group of cars driving next to each other. The speed of the car fleet is the minimum speed of any car in the fleet.

If a car catches up to a car fleet at the mile target, it will still be considered as part of the car fleet.

Return the number of car fleets that will arrive at the destination.

**Example 1:**
```
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3

Explanation:
- Cars at positions 10 (speed 2) and 8 (speed 4) become a fleet, meeting at 12
- Car at position 0 (speed 1) is a fleet by itself
- Cars at positions 5 (speed 1) and 3 (speed 3) become a fleet, meeting at 6
```

**Example 2:**
```
Input: target = 10, position = [3], speed = [3]
Output: 1
```

**Example 3:**
```
Input: target = 100, position = [0,2,4], speed = [4,2,1]
Output: 1
```

**Constraints:**
- `n == position.length == speed.length`
- `1 <= n <= 10^5`
- `0 < target <= 10^6`
- `0 <= position[i] < target`
- All the values of position are unique
- `0 < speed[i] <= 10^6`

## Observations

### Key Insights

1. **Time to reach target is what matters**: Each car has a time to reach the target: `time = (target - position) / speed`

2. **Cars closer to target determine fleet formation**: 
   - A car ahead (closer to target) acts as a "blocker" for cars behind it
   - Cars behind can catch up but cannot pass
   - If a car behind reaches the target faster, it will catch up and form a fleet

3. **Process from right to left (closest to target first)**:
   - Start with the car closest to target
   - For each subsequent car (going backward), check if it can catch up to the fleet ahead
   - If a car takes **longer** to reach the target than all cars ahead of it, it forms a **new fleet**

4. **When does a new fleet form?**
   - If `current_car_time > max_time_ahead`, this car is slower and won't catch up
   - This car becomes the start of a new fleet
   - All subsequent cars will compare against this new maximum time

5. **Stack usage**: The stack keeps track of cars in the current fleet being formed

## Solution

### Approach: Sort by Position + Greedy with Time Tracking

```python
class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        # Sort cars by their starting position
        cars = sorted([pair for pair in zip(position, speed)], key=lambda x: x[0])
        
        count = 0
        st = []  # Stack to track current fleet
        n = len(cars)
        cur_max_time = 0  # Maximum time in current fleet
        
        # Process from rightmost car (closest to target) to leftmost
        for i in range(n - 1, -1, -1):
            pos, s = cars[i]
            time = (target - pos) / s  # Time for this car to reach target
            
            # If this car takes longer than any car ahead, it forms a new fleet
            if st and cur_max_time < time:
                count += 1  # Previous fleet is complete
                st = []  # Start new fleet
                cur_max_time = 0
            
            # Update maximum time (slowest car in current fleet)
            cur_max_time = max(cur_max_time, time)
            st.append(time)
        
        # Don't forget the last fleet
        if st:
            count += 1
        
        return count
```

### Algorithm Walkthrough

**Example 1**: `target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]`

1. **Sort by position**: `[(0,1), (3,3), (5,1), (8,4), (10,2)]`

2. **Calculate times**: 
   - Car at pos 10: time = (12-10)/2 = 1.0
   - Car at pos 8: time = (12-8)/4 = 1.0
   - Car at pos 5: time = (12-5)/1 = 7.0
   - Car at pos 3: time = (12-3)/3 = 3.0
   - Car at pos 0: time = (12-0)/1 = 12.0

3. **Process from right to left**:
   - `i=4` (pos=10): time=1.0, st=[1.0], cur_max_time=1.0
   - `i=3` (pos=8): time=1.0, cur_max_time=1.0 (same fleet)
   - `i=2` (pos=5): time=7.0 > 1.0 → **Fleet 1 complete**, count=1, reset, st=[7.0], cur_max_time=7.0
   - `i=1` (pos=3): time=3.0 < 7.0 → joins fleet, cur_max_time=7.0
   - `i=0` (pos=0): time=12.0 > 7.0 → **Fleet 2 complete**, count=2, reset, st=[12.0]
   - End: **Fleet 3**, count=3

**Output**: 3 ✓

### Complexity Analysis

- **Time Complexity**: $O(n \log n)$
  - Sorting: $O(n \log n)$
  - Single pass through cars: $O(n)$
  - Total: $O(n \log n)$

- **Space Complexity**: $O(n)$
  - Storing sorted pairs: $O(n)$
  - Stack can have at most $n$ elements: $O(n)$

### Alternative Approach (Cleaner)

The stack is not strictly necessary. We can simplify:

```python
class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        cars = sorted(zip(position, speed), reverse=True)  # Sort by position descending
        
        fleets = 0
        prev_time = 0
        
        for pos, spd in cars:
            time = (target - pos) / spd
            if time > prev_time:  # This car is slower, forms new fleet
                fleets += 1
                prev_time = time
        
        return fleets
```

# Tags

`Array` `Stack` `Sorting` `Greedy` `Monotonic Stack`

