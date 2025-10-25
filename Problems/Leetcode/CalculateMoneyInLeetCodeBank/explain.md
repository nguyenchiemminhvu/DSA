## Problem

https://leetcode.com/problems/calculate-money-in-leetcode-bank/description/

```
Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.

He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday, he will put in $1 more than the day before. On every subsequent Monday, he will put in $1 more than the previous Monday.

Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth day.

Example 1:

Input: n = 4
Output: 10
Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.

Example 2:

Input: n = 10
Output: 37
Explanation: After the 10th day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4) = 37. Notice that on the 2nd Monday, Hercy only puts in $2.

Example 3:

Input: n = 20
Output: 96
Explanation: After the 20th day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4 + 5 + 6 + 7 + 8) + (3 + 4 + 5 + 6 + 7 + 8) = 96.

Constraints:

1 <= n <= 1000
```

## Observations

1. **Weekly Pattern**: The problem follows a weekly pattern where:
   - Week 1: 1, 2, 3, 4, 5, 6, 7 (sum = 28)
   - Week 2: 2, 3, 4, 5, 6, 7, 8 (sum = 35)
   - Week 3: 3, 4, 5, 6, 7, 8, 9 (sum = 42)
   - Each week starts with one more dollar than the previous week's Monday

2. **Mathematical Pattern**: For week k (1-indexed):
   - Monday of week k: k dollars
   - The week's sequence: k, k+1, k+2, k+3, k+4, k+5, k+6
   - Sum of week k = k + (k+1) + (k+2) + (k+3) + (k+4) + (k+5) + (k+6) = 7k + 21

3. **Two Cases to Handle**:
   - Complete weeks: Calculate sum for all full weeks
   - Remaining days: Calculate sum for partial week if any days remain

4. **Arithmetic Sequence**: Each week forms an arithmetic sequence with:
   - First term: k (Monday of week k)
   - Last term: k+6 (Sunday of week k)
   - Number of terms: 7

## Solution

The solution uses an efficient mathematical approach rather than simulation:

### Algorithm:
1. **Process Complete Weeks**: 
   - Count how many complete weeks (7 days) fit in n days
   - For each complete week k, calculate the sum using arithmetic sequence formula
   - Use helper function `sum_a_to_b(a, b)` which calculates sum from a to b: `(b-a+1)*(a+b)/2`

2. **Handle Remaining Days**:
   - If there are leftover days after complete weeks, calculate their sum
   - These days start from the next Monday value and continue sequentially

### Example Walkthrough (n = 10):
- Complete weeks: 1 week (days 1-7)
  - Week 1: sum_a_to_b(1, 7) = 7*8/2 = 28
- Remaining days: 3 days (days 8-10)
  - Week 2 partial: sum_a_to_b(2, 4) = 3*6/2 = 9
- Total: 28 + 9 = 37

### Time Complexity: O(n/7) = O(n)
### Space Complexity: O(1)

The key insight is recognizing the arithmetic sequence pattern within each week and using the mathematical formula instead of simulating day by day.

## Tags

math, simulation