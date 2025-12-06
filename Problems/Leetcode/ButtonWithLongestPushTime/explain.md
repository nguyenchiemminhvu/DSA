## Problem

https://leetcode.com/problems/button-with-longest-push-time/

```
You are given a 2D array events which represents a sequence of events where a child pushes a series of buttons on a keyboard.

Each events[i] = [indexi, timei] indicates that the button at index indexi was pressed at time timei.

The array is sorted in increasing order of time.
The time taken to press a button is the difference in time between consecutive button presses. 
The time for the first button is simply the time at which it was pressed.

Return the index of the button that took the longest time to push. 
If multiple buttons have the same longest time, return the button with the smallest index.

Example 1:
Input: events = [[1,2],[2,5],[3,9],[1,15]]
Output: 1
Explanation:
- Button with index 1 is pressed at time 2.
- Button with index 2 is pressed at time 5, so it took 5 - 2 = 3 units of time.
- Button with index 3 is pressed at time 9, so it took 9 - 5 = 4 units of time.
- Button with index 1 is pressed again at time 15, so it took 15 - 9 = 6 units of time.

Example 2:
Input: events = [[10,5],[1,7]]
Output: 10
Explanation:
- Button with index 10 is pressed at time 5.
- Button with index 1 is pressed at time 7, so it took 7 - 5 = 2 units of time.

Constraints:
- 1 <= events.length <= 1000
- events[i] == [indexi, timei]
- 1 <= indexi, timei <= 10^5
- The input is generated such that events is sorted in increasing order of timei.
```

## Observations

1. **Time Calculation**: The duration for each button press is calculated as the difference between the current timestamp and the previous timestamp. For the first button, the duration is just the timestamp itself (difference from time 0).

2. **Same Button Multiple Times**: A button can be pressed multiple times with different durations. We need to track the maximum duration for each button index.

3. **Tie-Breaking Rule**: When multiple buttons have the same longest duration, we should return the button with the smallest index.

4. **Sequential Processing**: Since events are sorted by time, we can process them in order while keeping track of the previous timestamp.

5. **Edge Cases**:
   - Single event: Return the index of that button
   - All buttons have equal duration: Return the smallest index
   - Same button pressed multiple times: Track its maximum duration

## Solution

### Approach: Single Pass with HashMap

**Algorithm:**
1. Use a hashmap to store the maximum duration for each button index
2. Iterate through events while maintaining:
   - `prev_time`: The timestamp of the previous event
   - `max_duration`: The maximum duration seen so far
   - `max_key`: The button index with the maximum duration
3. For each event:
   - Calculate duration = current_time - prev_time
   - Update the button's maximum duration in the hashmap
   - Update max_duration and max_key if we found a longer duration
   - If duration equals max_duration, update max_key to the smaller index
4. Return max_key

**Time Complexity:** O(n) where n is the number of events
- Single pass through all events

**Space Complexity:** O(k) where k is the number of unique button indices
- Hashmap stores at most k entries

**Key Points:**
- The hashmap `m` stores the maximum duration for each button across all its presses
- We track both the global maximum duration and its corresponding button index
- The tie-breaking logic ensures we return the smallest index when durations are equal
- Starting with `prev_time = 0` correctly handles the first button press

# Tags
Array, Hash Table, Greedy, Simulation

