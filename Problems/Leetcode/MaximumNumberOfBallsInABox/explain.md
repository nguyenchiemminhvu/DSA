## Problem

https://leetcode.com/problems/maximum-number-of-balls-in-a-box/

```
You are working in a ball factory where you have n balls numbered from lowLimit up to highLimit inclusive (i.e., n == highLimit - lowLimit + 1), and an infinite number of boxes numbered from 1 to infinity.

Your job at this factory is to put each ball in the box with a number equal to the sum of digits of the ball's number. For example, the ball number 321 will be put in the box number 3 + 2 + 1 = 6 and the ball number 10 will be put in the box number 1 + 0 = 1.

Given two integers lowLimit and highLimit, return the number of balls in the box with the most balls.

Example 1:

Input: lowLimit = 1, highLimit = 10
Output: 2
Explanation:
Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
Ball Count:  2 1 1 1 1 1 1 1 1 0  0  ...
Box 1 has the most number of balls with 2 balls.

Example 2:

Input: lowLimit = 5, highLimit = 15
Output: 2
Explanation:
Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
Ball Count:  1 1 1 1 2 2 1 1 1 0  0  ...
Boxes 5 and 6 have the most number of balls with 2 balls in each.

Example 3:

Input: lowLimit = 19, highLimit = 28
Output: 2
Explanation:
Box Number:  1 2 3 4 5 6 7 8 9 10 11 12 ...
Ball Count:  0 1 1 1 1 1 1 1 1 2  0  0  ...
Box 10 has the most number of balls with 2 balls.

Constraints:

1 <= lowLimit <= highLimit <= 105
```

## Observations

1. **Problem Understanding**: We need to place balls numbered from `lowLimit` to `highLimit` into boxes where each box number equals the sum of digits of the ball's number.

2. **Key Insight**: The sum of digits for any number in the given range [1, 10^5] will be at most 9×5 = 45 (for number 99999). This means we'll have at most 45 different boxes.

3. **Pattern Analysis**: 
   - Ball 1 → Box 1 (sum = 1)
   - Ball 10 → Box 1 (sum = 1+0 = 1) 
   - Ball 19 → Box 10 (sum = 1+9 = 10)
   - Ball 28 → Box 10 (sum = 2+8 = 10)

4. **Frequency Counting**: We need to count how many balls go into each box and find the box with maximum count.

5. **Time Complexity**: O(n × d) where n = highLimit - lowLimit + 1 and d is average number of digits
6. **Space Complexity**: O(k) where k is number of unique digit sums (at most 45)

## Solution

The solution uses a straightforward approach:

1. **Helper Function `sum_digit(val)`**:
   - Calculates the sum of digits of a number
   - Uses modulo 10 to get the last digit and integer division to remove it
   - Continues until the number becomes 0

2. **Main Algorithm**:
   - Create a frequency dictionary `f` to count balls in each box
   - Iterate through each ball number from `lowLimit` to `highLimit`
   - For each ball, calculate its digit sum using `sum_digit()`
   - Increment the count for that box number in the dictionary
   - Return the maximum count among all boxes

3. **Example Walkthrough** (lowLimit=1, highLimit=10):
   - Ball 1 → Box 1, Ball 2 → Box 2, ..., Ball 9 → Box 9
   - Ball 10 → Box 1 (1+0=1)
   - Box 1 has 2 balls (balls 1 and 10), others have 1 ball each
   - Maximum is 2

# Tags

Hash Table, Math, Simulation

