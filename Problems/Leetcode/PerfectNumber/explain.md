## Problem

https://leetcode.com/problems/perfect-number/description

```
A perfect number is a positive integer that is equal to the sum of its positive divisors, excluding the number itself. A divisor of an integer x is an integer that can divide x evenly.

Given an integer n, return true if n is a perfect number, otherwise return false.

Example 1:

Input: num = 28
Output: true
Explanation: 28 = 1 + 2 + 4 + 7 + 14
1, 2, 4, 7, and 14 are all divisors of 28.

Example 2:

Input: num = 7
Output: false

Constraints:

1 <= num <= 108
```

## Observations

1. **Perfect Number Definition**: A perfect number equals the sum of its proper positive divisors (divisors excluding the number itself).

2. **Divisor Pairs**: For any divisor `d` of number `n`, there exists a complementary divisor `n/d`. This means we only need to check up to √n to find all divisors efficiently.

3. **Edge Cases**: 
   - The number 1 has no proper divisors (only divisor is 1 itself), so it's not a perfect number
   - We need to be careful not to double-count square roots (when `d * d = n`)
   - We must exclude the number itself from the sum

4. **Optimization**: Instead of checking all numbers from 1 to n-1, we can check only from 1 to √n and find divisor pairs, reducing time complexity from O(n) to O(√n).

5. **Known Perfect Numbers**: The first few perfect numbers are 6, 28, 496, 8128... They become very rare as numbers get larger.

## Solution

1. **Special Case Handling**: First check if `num == 1`. Since 1 has no proper divisors, it cannot be a perfect number.

2. **Find Divisors Function**:
   - Calculate the square root boundary: `s = int(math.sqrt(val) + 1)`
   - Iterate from 1 to √n (exclusive of √n to avoid including the number itself)
   - For each `i` that divides `val`:
     - Add `i` to the divisors list
     - Add the complementary divisor `val // i` if:
       - `i * i != val` (to avoid double-counting perfect squares)
       - `val // i != val` (to exclude the number itself)

3. **Validation**: Sum all found divisors and check if it equals the original number.

**Time Complexity**: O(√n) - we only iterate up to the square root of the number.

**Space Complexity**: O(d) where d is the number of divisors, which is at most O(√n) in the worst case.

**Example Walkthrough** (num = 28):
- Check divisors from 1 to √28 ≈ 5.3, so check 1, 2, 3, 4, 5
- i=1: 28%1=0 → add 1 and 28//1=28, but 28//1==28 so only add 1
- i=2: 28%2=0 → add 2 and 28//2=14
- i=3: 28%3≠0 → skip
- i=4: 28%4=0 → add 4 and 28//4=7
- i=5: 28%5≠0 → skip
- Divisors: [1, 2, 14, 4, 7]
- Sum: 1+2+14+4+7 = 28 ✓

# Tags

Math, Number Theory, Divisors

