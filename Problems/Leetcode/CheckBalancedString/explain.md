## Problem

https://leetcode.com/problems/check-balanced-string/description/

```
You are given a string num consisting of only digits. A string of digits is called balanced if the sum of the digits at even indices is equal to the sum of digits at odd indices.

Return true if num is balanced, otherwise return false.

Example 1:

Input: num = "1234"

Output: false

Explanation:

The sum of digits at even indices is 1 + 3 == 4, and the sum of digits at odd indices is 2 + 4 == 6.
Since 4 is not equal to 6, num is not balanced.

Example 2:

Input: num = "24123"

Output: true

Explanation:

The sum of digits at even indices is 2 + 1 + 3 == 6, and the sum of digits at odd indices is 4 + 2 == 6.
Since both are equal the num is balanced.

Constraints:

2 <= num.length <= 100
num consists of digits only
```

## Observations

1. **Problem Understanding**: We need to check if the sum of digits at even indices equals the sum of digits at odd indices.
   - Even indices: 0, 2, 4, 6, ...
   - Odd indices: 1, 3, 5, 7, ...

2. **Key Insights**:
   - We can iterate through the string once and accumulate sums based on index parity
   - Index parity can be determined using bitwise AND operation: `i & 1`
   - `i & 1` returns 0 for even indices and 1 for odd indices
   - We need to convert character digits to integers using `ord(char) - ord('0')`

3. **Examples Analysis**:
   - "1234": Even positions (0,2): 1+3=4, Odd positions (1,3): 2+4=6 → Not balanced
   - "24123": Even positions (0,2,4): 2+1+3=6, Odd positions (1,3): 4+2=6 → Balanced

## Solution

1. **Initialize**: Create array `arr = [0, 0]` where:
   - `arr[0]` stores sum of digits at even indices
   - `arr[1]` stores sum of digits at odd indices

2. **Iterate**: For each character at index `i`:
   - Use `(i & 1)` to determine if index is even (0) or odd (1)
   - Convert character to digit using `ord(num[i]) - ord('0')`
   - Add the digit to the appropriate sum

3. **Compare**: Return `True` if both sums are equal, `False` otherwise

**Time Complexity**: O(n) where n is the length of the string
**Space Complexity**: O(1) using only a fixed-size array

**Bitwise Operation Explanation**:
- `i & 1` performs bitwise AND between `i` and `1`
- Since 1 in binary is `...0001`, this operation isolates the least significant bit
- Even numbers have LSB = 0, odd numbers have LSB = 1
- This gives us a direct mapping: even index → 0, odd index → 1

# Tags

Array, String, Bit Manipulation, Math

