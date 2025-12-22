## Problem

https://leetcode.com/problems/mirror-distance-of-an-integer/description/

You are given an integer `n`.

Define its **mirror distance** as: `abs(n - reverse(n))` where `reverse(n)` is the integer formed by reversing the digits of `n`.

Return an integer denoting the mirror distance of `n`.

**Note:** `abs(x)` denotes the absolute value of x.

**Example 1:**
```
Input: n = 25
Output: 27
Explanation:
reverse(25) = 52
Thus, the answer is abs(25 - 52) = 27
```

**Example 2:**
```
Input: n = 10
Output: 9
Explanation:
reverse(10) = 01 which is 1
Thus, the answer is abs(10 - 1) = 9
```

**Example 3:**
```
Input: n = 7
Output: 0
Explanation:
reverse(7) = 7
Thus, the answer is abs(7 - 7) = 0
```

**Constraints:**
- `1 <= n <= 10^9`

## Observations

1. **Single-digit numbers**: For single-digit numbers (1-9), the reverse is the same as the original number, so the mirror distance is always 0.

2. **Palindromes**: For palindromic numbers (e.g., 121, 343), the reverse equals the original, resulting in a mirror distance of 0.

3. **Leading zeros**: When reversing a number that ends with zeros (e.g., 10, 100, 1230), the leading zeros in the reversed number are dropped. For example:
   - `reverse(10) = 01 = 1`
   - `reverse(100) = 001 = 1`
   - `reverse(1230) = 0321 = 321`

4. **Digit manipulation**: The problem requires extracting and reversing digits without using string operations, which is a common algorithmic pattern.

5. **Mathematical approach**: We can reverse a number mathematically by:
   - Extracting the last digit using modulo operation (`n % 10`)
   - Building the reversed number by multiplying by 10 and adding the extracted digit
   - Removing the last digit from the original using integer division (`n // 10`)

## Solution

### Approach: Mathematical Digit Reversal

The solution uses a mathematical approach to reverse the digits of the integer:

```python
class Solution:
    def mirrorDistance(self, n: int) -> int:
        rev = 0
        temp = n
        while temp:
            rev = rev * 10 + (temp % 10)
            temp //= 10
        return abs(n - rev)
```

**Algorithm:**

1. **Initialize variables:**
   - `rev = 0`: Stores the reversed number
   - `temp = n`: Working copy to avoid modifying the original number

2. **Reverse the digits:**
   - While `temp` is not zero:
     - Extract the last digit: `temp % 10`
     - Append it to `rev`: `rev = rev * 10 + (temp % 10)`
     - Remove the last digit from `temp`: `temp //= 10`

3. **Calculate mirror distance:**
   - Return `abs(n - rev)`

**Example walkthrough (n = 25):**
```
Initial: temp = 25, rev = 0

Iteration 1:
  - Extract: 25 % 10 = 5
  - Update rev: 0 * 10 + 5 = 5
  - Update temp: 25 // 10 = 2

Iteration 2:
  - Extract: 2 % 10 = 2
  - Update rev: 5 * 10 + 2 = 52
  - Update temp: 2 // 10 = 0

Loop ends (temp = 0)
Result: abs(25 - 52) = 27
```

**Example walkthrough (n = 10):**
```
Initial: temp = 10, rev = 0

Iteration 1:
  - Extract: 10 % 10 = 0
  - Update rev: 0 * 10 + 0 = 0
  - Update temp: 10 // 10 = 1

Iteration 2:
  - Extract: 1 % 10 = 1
  - Update rev: 0 * 10 + 1 = 1
  - Update temp: 1 // 10 = 0

Loop ends (temp = 0)
Result: abs(10 - 1) = 9
```

### Complexity Analysis

- **Time Complexity:** O(d), where d is the number of digits in n
  - We iterate through each digit once
  - For n ≤ 10^9, we have at most 10 digits
  - Effectively O(log₁₀(n))

- **Space Complexity:** O(1)
  - Only uses constant extra space for variables `rev` and `temp`
  - No additional data structures required

### Alternative Approaches

While the mathematical approach is efficient, alternative methods include:

1. **String conversion:**
   ```python
   def mirrorDistance(self, n: int) -> int:
       rev = int(str(n)[::-1])
       return abs(n - rev)
   ```
   - Simpler but involves string operations
   - Still O(d) time, but with potential overhead from string operations

# Tags

`Math` `Number Theory` `Digit Manipulation`

