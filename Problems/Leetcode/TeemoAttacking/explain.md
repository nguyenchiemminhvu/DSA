## Problem

https://leetcode.com/problems/teemo-attacking/description/

```
Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for a exactly duration seconds. More formally, an attack at second t will mean Ashe is poisoned during the inclusive time interval [t, t + duration - 1]. If Teemo attacks again before the poison effect ends, the timer for it is reset, and the poison effect will end duration seconds after the new attack.

You are given a non-decreasing integer array timeSeries, where timeSeries[i] denotes that Teemo attacks Ashe at second timeSeries[i], and an integer duration.

Return the total number of seconds that Ashe is poisoned.

Example 1:

Input: timeSeries = [1,4], duration = 2
Output: 4
Explanation: Teemo's attacks on Ashe go as follows:
- At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
- At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.

Example 2:

Input: timeSeries = [1,2], duration = 2
Output: 3
Explanation: Teemo's attacks on Ashe go as follows:
- At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
- At second 2 however, Teemo attacks again and resets the poison timer. Ashe is poisoned for seconds 2 and 3.
Ashe is poisoned for seconds 1, 2, and 3, which is 3 seconds in total.

Constraints:

1 <= timeSeries.length <= 104
0 <= timeSeries[i], duration <= 107
timeSeries is sorted in non-decreasing order.
```

## Observations

1. **Time Intervals**: Each attack creates a poison effect that lasts for `duration` seconds, starting from the attack time.
   - Attack at time `t` creates poison interval `[t, t + duration - 1]`

2. **Overlapping Effects**: If a new attack happens while the poison is still active, the timer resets.
   - This means overlapping poison intervals merge into one continuous period
   - We only count the actual poisoned time, not the overlapped portions

3. **Key Insight**: We need to track intervals and merge overlapping ones.
   - When attacks are close together (gap < duration), intervals overlap
   - When attacks are far apart (gap ≥ duration), intervals are separate

4. **Algorithm Approach**: 
   - Track the current poison interval with `start` and `end` times
   - For each new attack, decide whether to extend current interval or start a new one
   - Add completed intervals to the total duration

## Solution

The solution uses a **greedy interval merging** approach:

```python
def findPoisonedDuration(self, timeSeries: List[int], duration: int) -> int:
    total_duration = 0
    
    start = timeSeries[0]           # Start of current poison interval
    end = start + duration          # End of current poison interval
    
    for t in timeSeries:
        if t >= end:                # No overlap - current interval ends
            total_duration += end - start    # Add completed interval
            start = t               # Start new interval
        end = t + duration          # Update end time (extend or new interval)
    
    return total_duration + (end - start)  # Add the last interval
```

**Step-by-step breakdown:**

1. **Initialize**: Start with the first attack creating interval `[timeSeries[0], timeSeries[0] + duration)`

2. **Process each attack**:
   - If `t >= end`: The new attack starts after current poison ends
     - Add current interval duration to total: `end - start`
     - Start new interval at time `t`
   - Always update `end = t + duration` (either extends current or sets new interval end)

3. **Final step**: Add the last interval duration: `end - start`

**Example walkthrough** (timeSeries = [1,2], duration = 2):
- Initial: start=1, end=3 (interval [1,3))
- t=1: t < end, so extend. end=3
- t=2: t < end, so extend. end=4 (interval [1,4))
- Final: total_duration = 0 + (4-1) = 3

**Time Complexity**: O(n) - single pass through timeSeries
**Space Complexity**: O(1) - only using constant extra space

## Tags

array, greedy