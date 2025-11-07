## Problem

https://leetcode.com/problems/n-th-tribonacci-number/description/

```
The Tribonacci sequence Tn is defined as follows: 

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.

Example 1:

Input: n = 4
Output: 4
Explanation:
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

Example 2:

Input: n = 25
Output: 1389537

Constraints:

0 <= n <= 37
The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.
```

## Observations

1. **Sequence Pattern**: The Tribonacci sequence follows a recurrence relation where each number is the sum of the three preceding numbers.
   - T₀ = 0, T₁ = 1, T₂ = 1
   - T₃ = T₀ + T₁ + T₂ = 0 + 1 + 1 = 2
   - T₄ = T₁ + T₂ + T₃ = 1 + 1 + 2 = 4
   - And so on...

2. **Base Cases**: The first three values are predefined and need special handling.

3. **Iterative Approach**: Since we only need the previous 3 values to calculate the next one, we can use a space-efficient iterative approach instead of storing all values.

4. **Constraints**: With n ≤ 37, the result fits in a 32-bit integer, so we don't need to worry about overflow.

## Solution

1. **Initialize Variables**: We use three variables `a`, `b`, `c` to represent T₀, T₁, T₂ respectively.

2. **Handle Base Cases**: 
   - For n = 0, return 0
   - For n = 1, return 1  
   - For n = 2, return 1

3. **Iterative Calculation**:
   - For n > 2, we iterate (n-2) times
   - In each iteration, we slide the window: `a, b, c = b, c, a + b + c`
   - This means:
     - New `a` = old `b` (shift left)
     - New `b` = old `c` (shift left)
     - New `c` = old `a` + old `b` + old `c` (sum of all three)

4. **Return Result**: After the loop, `c` contains the n-th Tribonacci number.

**Time Complexity**: O(n) - We iterate n-2 times for n > 2
**Space Complexity**: O(1) - Only using three variables regardless of input size

### Example Walkthrough (n = 4):
- Initial: a=0, b=1, c=1 (T₀, T₁, T₂)
- Iteration 1: a=1, b=1, c=2 (T₁, T₂, T₃)
- Iteration 2: a=1, b=2, c=4 (T₂, T₃, T₄)
- Result: 4

# Tags

- Dynamic Programming
- Math
- Sequence
- Space Optimization

