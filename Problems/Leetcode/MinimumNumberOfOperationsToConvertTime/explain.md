## Problem

https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/description/

```
You are given two strings current and correct representing two 24-hour times.

24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest is 23:59.

In one operation you can increase the time current by 1, 5, 15, or 60 minutes. You can perform this operation any number of times.

Return the minimum number of operations needed to convert current to correct.

Example 1:

Input: current = "02:30", correct = "04:35"
Output: 3
Explanation:
We can convert current to correct in 3 operations as follows:
- Add 60 minutes to current. current becomes "03:30".
- Add 60 minutes to current. current becomes "04:30".
- Add 5 minutes to current. current becomes "04:35".
It can be proven that it is not possible to convert current to correct in fewer than 3 operations.

Example 2:

Input: current = "11:00", correct = "11:01"
Output: 1
Explanation: We only have to add one minute to current, so the minimum number of operations needed is 1.

Constraints:

current and correct are in the format "HH:MM"
current <= correct
```

## Observations

1. **Time Format**: Both times are in "HH:MM" format, where we can extract hours and minutes separately.

2. **Operations Available**: We can add 1, 5, 15, or 60 minutes in each operation. This suggests a greedy approach - always use the largest possible increment.

3. **Time Conversion**: We need to convert both times to a common unit (minutes) for easier calculation.

4. **Circular Time**: Since we're dealing with 24-hour format, if the target time is "earlier" than current time (e.g., current = "23:30", correct = "01:00"), we need to account for crossing midnight (24 hours = 1440 minutes).

5. **Greedy Strategy**: To minimize operations, we should always use the largest possible increment first:
   - Use 60 minutes when possible (1 hour)
   - Use 15 minutes when possible (quarter hour)
   - Use 5 minutes when possible
   - Use 1 minute for the remainder

6. **Edge Case**: If current and correct times are the same, no operations are needed.

## Solution

### Approach: Greedy Algorithm

The key insight is that to minimize the number of operations, we should always use the largest possible increment (60, 15, 5, or 1 minute) at each step.

### Algorithm Steps:

1. **Convert times to minutes**: Convert both current and correct times from "HH:MM" format to total minutes since 00:00.
   - `total_minutes = hours * 60 + minutes`

2. **Calculate time difference**: 
   - If `current < correct`: `diff = correct - current`
   - If `current >= correct`: We need to cross midnight, so `diff = (1440 - current) + correct`
   - Special case: If times are equal, return 0

3. **Apply greedy strategy**: Use the largest possible increments first:
   - Use as many 60-minute increments as possible
   - Use as many 15-minute increments as possible for remainder
   - Use as many 5-minute increments as possible for remainder
   - Use 1-minute increments for final remainder

### Example Walkthrough:

**Example 1**: `current = "02:30"`, `correct = "04:35"`
- `cur_min = 2*60 + 30 = 150 minutes`
- `cor_min = 4*60 + 35 = 275 minutes`
- `diff = 275 - 150 = 125 minutes`
- Operations:
  1. `125 >= 60` → subtract 60, `diff = 65`, operations = 1
  2. `65 >= 60` → subtract 60, `diff = 5`, operations = 2
  3. `5 >= 5` → subtract 5, `diff = 0`, operations = 3
- Result: 3 operations

**Example 2**: `current = "11:00"`, `correct = "11:01"`
- `cur_min = 11*60 + 0 = 660 minutes`
- `cor_min = 11*60 + 1 = 661 minutes`
- `diff = 661 - 660 = 1 minute`
- Operations:
  1. `1 < 60, 1 < 15, 1 < 5` → subtract 1, `diff = 0`, operations = 1
- Result: 1 operation

### Time Complexity: O(diff/60)
- In the worst case, we need to process `diff` minutes
- Since we use 60-minute increments when possible, the loop runs at most `diff/60 + diff%60` times
- This simplifies to O(diff), where diff is at most 1439 minutes (less than 24 hours)

### Space Complexity: O(1)
- Only using a constant amount of extra space for variables

### Alternative Optimized Approach:

We can make this more efficient by calculating the number of each type of operation directly:

```python
class Solution:
    def convertTime(self, current: str, correct: str) -> int:
        cur_min = int(current[0:2]) * 60 + int(current[3:])
        cor_min = int(correct[0:2]) * 60 + int(correct[3:])
        
        if cur_min == cor_min:
            return 0
        
        diff = (cor_min - cur_min) if cur_min < cor_min else (1440 - cur_min + cor_min)
        
        # Calculate operations directly
        operations = 0
        operations += diff // 60    # 60-minute operations
        diff %= 60
        operations += diff // 15    # 15-minute operations
        diff %= 15
        operations += diff // 5     # 5-minute operations
        diff %= 5
        operations += diff          # 1-minute operations
        
        return operations
```

This optimized version has O(1) time complexity.
## Tags

string, greedy