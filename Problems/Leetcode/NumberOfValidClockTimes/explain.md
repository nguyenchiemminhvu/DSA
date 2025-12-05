## Problem

https://leetcode.com/problems/number-of-valid-clock-times/description/

```
You are given a string of length 5 called time, representing the current time on a digital clock in the format "hh:mm". The earliest possible time is "00:00" and the latest possible time is "23:59".

In the string time, the digits represented by the ? symbol are unknown, and must be replaced with a digit from 0 to 9.

Return an integer answer, the number of valid clock times that can be created by replacing every ? with a digit from 0 to 9.

Example 1:

Input: time = "?5:00"
Output: 2
Explanation: We can replace the ? with either a 0 or 1, producing "05:00" or "15:00". Note that we cannot replace it with a 2, since the time "25:00" is invalid. In total, we have two choices.

Example 2:

Input: time = "0?:0?"
Output: 100
Explanation: Each ? can be replaced by any digit from 0 to 9, so we have 100 total choices.

Example 3:

Input: time = "??:??"
Output: 1440
Explanation: There are 24 possible choices for the hours, and 60 possible choices for the minutes. In total, we have 24 * 60 = 1440 choices.

Constraints:

time is a valid string of length 5 in the format "hh:mm".
"00" <= hh <= "23"
"00" <= mm <= "59"
Some of the digits might be replaced with '?' and need to be replaced with digits from 0 to 9.
```

## Observations

1. **Time Format**: The time is in "hh:mm" format where:
   - Hours: 00-23 (24-hour format)
   - Minutes: 00-59 (standard minutes)

2. **Question Mark Constraints**: Each `?` can be replaced with any digit 0-9, but the resulting time must be valid.

3. **Position Dependencies**: The valid digits for each position depend on:
   - **Position 0 (first hour digit)**: Can be 0, 1, or 2
   - **Position 1 (second hour digit)**: Depends on the first hour digit
     - If first digit is 0 or 1: can be 0-9
     - If first digit is 2: can only be 0-3
   - **Position 3 (first minute digit)**: Can be 0-5 (since max minutes is 59)
   - **Position 4 (second minute digit)**: Can be 0-9

4. **Independence**: Hours and minutes are independent - we can multiply the number of valid hour combinations by the number of valid minute combinations.

5. **Cases to Handle**:
   - Both hour digits are `?`
   - Only first hour digit is `?`
   - Only second hour digit is `?`
   - Neither hour digit is `?`
   - Similar cases for minutes

## Solution

**Approach**: Count valid combinations for hours and minutes separately, then multiply.

### Algorithm Steps:

1. **Parse the input**: Split into hour part and minute part
2. **Count valid hours**: 
   - If both digits are `?`: 24 possibilities (00-23)
   - If first digit is `?`: count based on second digit constraints
   - If second digit is `?`: count based on first digit constraints
   - If no `?` in hours: 1 possibility (if valid) or 0 (if invalid)
3. **Count valid minutes**:
   - If both digits are `?`: 60 possibilities (00-59)
   - If first digit is `?`: can be 0-5, so 6 possibilities
   - If second digit is `?`: can be 0-9, so 10 possibilities
   - If no `?` in minutes: 1 possibility (if valid) or 0 (if invalid)
4. **Return**: hours_count × minutes_count

### Detailed Logic:

**For Hours (`h1h2`):**
- `??`: 24 valid hours (00-23)
- `?d`: If d ≤ 3, then h1 can be 0,1,2 (3 choices). If d > 3, then h1 can be 0,1 (2 choices)
- `d?`: If d = 0 or 1, then h2 can be 0-9 (10 choices). If d = 2, then h2 can be 0-3 (4 choices)
- `dd`: Check if valid (00-23), return 1 if valid, 0 if not

**For Minutes (`m1m2`):**
- `??`: 60 valid minutes (00-59)
- `?d`: m1 can be 0-5 (6 choices)
- `d?`: m2 can be 0-9 (10 choices)
- `dd`: Check if valid (00-59), return 1 if valid, 0 if not

**Time Complexity**: O(1) - constant time operations
**Space Complexity**: O(1) - only using a few variables

# Tags

