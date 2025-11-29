## Problem

https://leetcode.com/problems/count-distinct-numbers-on-board/description/

```
You are given a positive integer n, that is initially placed on a board. Every day, for 10^9 days, you perform the following procedure:

- For each number x present on the board, find all numbers 1 <= i <= n such that x % i == 1.
- Then, place those numbers on the board.

Return the number of distinct integers present on the board after 10^9 days have elapsed.

Note:
- Once a number is placed on the board, it will remain on it until the end.
- % stands for the modulo operation. For example, 14 % 3 is 2.

Example 1:
Input: n = 5
Output: 4
Explanation: Initially, 5 is present on the board. 
The next day, 2 and 4 will be added since 5 % 2 == 1 and 5 % 4 == 1. 
After that day, 3 will be added to the board because 4 % 3 == 1. 
At the end of a billion days, the distinct numbers on the board will be 2, 3, 4, and 5.

Example 2:
Input: n = 3
Output: 2
Explanation: 
Since 3 % 2 == 1, 2 will be added to the board. 
After a billion days, the only two distinct numbers on the board are 2 and 3.

Constraints:
- 1 <= n <= 100
```

## Observations

1. **Key Insight**: If `x % i == 1`, then `x = i * k + 1` for some integer k ≥ 1. This means `i = (x - 1) / k`.

2. **For any number x on the board**, we can add `i` where `x % i == 1`:
   - This means `x - 1` must be divisible by `i`
   - The largest such `i` is `x - 1` itself (when k = 1)
   - So from any number x, we can always add x - 1 to the board

3. **Cascading effect**: 
   - Starting with n, we get n - 1
   - From n - 1, we get n - 2
   - From n - 2, we get n - 3
   - This continues until we reach 2

4. **Why do we stop at 2?**
   - For x = 2: We need `2 % i == 1`, which means `i` divides `2 - 1 = 1`
   - The only divisor of 1 is 1 itself, and `1 <= i <= n`
   - But `2 % 1 == 0`, not 1, so we can't add any new numbers from 2

5. **Special case**: When n = 1, there's no number i where `1 % i == 1` (since `1 % 1 == 0`), so the board only contains 1.

6. **The answer**:
   - For n = 1: answer is 1
   - For n ≥ 2: we get all numbers from 2 to n, which is n - 1 distinct numbers

## Solution

The solution is surprisingly simple once we understand the pattern:

1. **Base case**: If n = 1, no new numbers can be added (since `1 % 1 = 0 ≠ 1`), so return 1.

2. **General case**: For n ≥ 2, the board will eventually contain all integers from 2 to n:
   - From n, we add n - 1 (since `n % (n-1) = 1`)
   - From n - 1, we add n - 2 (since `(n-1) % (n-2) = 1`)
   - This cascades down to 2
   - We cannot add 1 from 2 because `2 % 1 = 0 ≠ 1`
   
3. **Count**: The distinct numbers are {2, 3, 4, ..., n}, which gives us n - 1 numbers.

**Time Complexity**: O(1)  
**Space Complexity**: O(1)

# Tags
#math #number-theory #pattern #easy

