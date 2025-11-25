## Problem

https://leetcode.com/problems/smallest-integer-divisible-by-k/description/

```
Given a positive integer k, you need to find the length of the smallest positive integer n such that n is divisible by k, and n only contains the digit 1.

Return the length of n. If there is no such n, return -1.

Note: n may not fit in a 64-bit signed integer.

Example 1:
Input: k = 1
Output: 1
Explanation: The smallest answer is n = 1, which has length 1.

Example 2:
Input: k = 2
Output: -1
Explanation: There is no such positive integer n divisible by 2.

Example 3:
Input: k = 3
Output: 3
Explanation: The smallest answer is n = 111, which has length 3.

Constraints: 1 <= k <= 10^5
```

## Observations

1. **Key Insight**: We're looking for numbers made only of 1's (repunits): 1, 11, 111, 1111, etc.
2. **Mathematical Property**: A number consisting only of 1's can be expressed as (10^n - 1)/9
3. **Divisibility Check**: For a repunit to be divisible by k, we need (10^n - 1)/9 ≡ 0 (mod k)
4. **Critical Observation**: If k is divisible by 2 or 5, no repunit can be divisible by k
   - Repunits are always odd (end in 1), so they can't be divisible by 2
   - Repunits never end in 0 or 5, so they can't be divisible by 5
5. **Modular Arithmetic**: Instead of calculating large numbers, we can use modular arithmetic to track remainders

## Solution

1. **Early Termination**: If k is divisible by 2 or 5, return -1 immediately since no repunit can be divisible by such numbers.

2. **Modular Arithmetic Simulation**: 
   - Start with remainder = 0
   - For each length from 1 to k:
     - Calculate `remainder = (remainder * 10 + 1) % k`
     - This simulates building repunits: 1, 11, 111, 1111...
     - The formula works because: new_number = old_number * 10 + 1

3. **Pattern Recognition**: 
   - If remainder becomes 0, we found our answer
   - The loop runs at most k times because there are only k possible remainders (0 to k-1)
   - By the Pigeonhole Principle, if no solution exists within k iterations, none exists

4. **Time Complexity**: O(k)
5. **Space Complexity**: O(1)

**Why the algorithm works:**
- We're essentially computing 1 % k, 11 % k, 111 % k, etc.
- The sequence of remainders will eventually repeat (cycle)
- If 0 appears in this sequence, we have our answer
- If no 0 appears within k steps, no solution exists

# Tags
- Math
- Modular Arithmetic
- Number Theory
- Simulation

