## Problem

https://leetcode.com/problems/prime-in-diagonal/description/

You are given a 0-indexed two-dimensional integer array `nums`.

Return the largest prime number that lies on at least one of the diagonals of `nums`. In case, no prime is present on any of the diagonals, return 0.

**Note that:**
- An integer is prime if it is greater than 1 and has no positive integer divisors other than 1 and itself.
- An integer `val` is on one of the diagonals of `nums` if there exists an integer `i` for which `nums[i][i] = val` or an `i` for which `nums[i][nums.length - i - 1] = val`.

**Example 1:**
```
Input: nums = [[1,2,3],[5,6,7],[9,10,11]]
Output: 11
Explanation: The numbers 1, 3, 6, 9, and 11 are the only numbers present on at least one of the diagonals. Since 11 is the largest prime, we return 11.
```

**Example 2:**
```
Input: nums = [[1,2,3],[5,17,7],[9,11,10]]
Output: 17
Explanation: The numbers 1, 3, 9, 10, and 17 are all present on at least one of the diagonals. 17 is the largest prime, so we return 17.
```

**Constraints:**
- `1 <= nums.length <= 300`
- `nums.length == nums[i].length` (square matrix)
- `1 <= nums[i][j] <= 4*10^6`

## Observations

1. **Two Diagonals in a Square Matrix:**
   - **Main diagonal (top-left to bottom-right):** Elements at positions where `i == j` → `nums[i][i]`
   - **Anti-diagonal (top-right to bottom-left):** Elements at positions where `i + j == n - 1` → `nums[i][n - i - 1]`

2. **Prime Number Check:**
   - A number is prime if it's greater than 1 and only divisible by 1 and itself
   - We only need to check divisibility up to `√val` because if `val = a * b` and `a ≤ b`, then `a ≤ √val`
   - Special case: 2 is the only even prime number

3. **Approach:**
   - Iterate through both diagonals
   - For each value on a diagonal, check if it's prime
   - Keep track of the maximum prime found
   - Return the maximum (or 0 if no primes found)

4. **Edge Cases:**
   - Matrix with only 1 element
   - No prime numbers on diagonals
   - Diagonals may overlap at the center (for odd-sized matrices)

## Solution

**Time Complexity:** O(n × √m) where:
- n is the size of the matrix (n × n)
- m is the maximum value in the matrix (up to 4×10^6)
- We check at most 2n diagonal elements (some may overlap)
- Each prime check takes O(√m) time

**Space Complexity:** O(1) - only using a constant amount of extra space

**How It Works:**

1. **Helper Function `is_prime(val)`:**
   - Returns False for values ≤ 1
   - Returns True for val = 2 (the only even prime)
   - For other values, checks if any number from 2 to √val divides val evenly
   - If no divisors found, the number is prime

2. **Main Diagonal Traversal:**
   - Iterates from i = 0 to n-1
   - Checks `nums[i][i]` for each position
   - Updates result if a larger prime is found

3. **Anti-Diagonal Traversal:**
   - Iterates from i = 0 to n-1
   - Checks `nums[i][n - i - 1]` for each position
   - Updates result if a larger prime is found

4. **Result:**
   - Returns the maximum prime found, or 0 if no primes exist

**Example Walkthrough (Example 1):**
```
nums = [[1,2,3],
        [5,6,7],
        [9,10,11]]

Main diagonal: nums[0][0]=1, nums[1][1]=6, nums[2][2]=11
Anti-diagonal: nums[0][2]=3, nums[1][1]=6, nums[2][0]=9

Diagonal values: 1, 3, 6, 9, 11
Prime check:
- 1: Not prime (≤ 1)
- 3: Prime ✓
- 6: Not prime (6 % 2 == 0)
- 9: Not prime (9 % 3 == 0)
- 11: Prime ✓

Maximum prime: 11
```

# Tags

`Array` `Math` `Matrix` `Prime Numbers` `Number Theory`

