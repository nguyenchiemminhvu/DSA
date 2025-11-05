## Problem

https://leetcode.com/problems/add-to-array-form-of-integer/

```
The array-form of an integer num is an array representing its digits in left to right order.

For example, for num = 1321, the array form is [1,3,2,1].
Given num, the array-form of an integer, and an integer k, return the array-form of the integer num + k.

Example 1:

Input: num = [1,2,0,0], k = 34
Output: [1,2,3,4]
Explanation: 1200 + 34 = 1234

Example 2:

Input: num = [2,7,4], k = 181
Output: [4,5,5]
Explanation: 274 + 181 = 455

Example 3:

Input: num = [2,1,5], k = 806
Output: [1,0,2,1]
Explanation: 215 + 806 = 1021

Constraints:

1 <= num.length <= 104
0 <= num[i] <= 9
num does not contain any leading zeros except for the zero itself.
1 <= k <= 104
```

## Observations

This is a classic "addition with carry" problem where we need to add two numbers digit by digit, similar to how we manually add numbers on paper.

Key observations:
1. **Array representation**: `num` represents a number in array form (digits from left to right), while `k` is a regular integer
2. **Different lengths**: The two numbers may have different lengths, so we need to handle this gracefully
3. **Carry propagation**: When adding digits, we might get sums ≥ 10, requiring carry to the next position
4. **Result format**: Return the result in the same array format as the input

**Algorithm approach**:
1. Convert `k` to array form and reverse both arrays for easier processing (right-to-left)
2. Ensure both arrays have the same length by padding the shorter one with zeros
3. Add digits from right to left, handling carry
4. If there's a final carry, append it
5. Reverse the result back to get the correct order

## Solution

```python
class Solution:
    def addToArrayForm(self, num: List[int], k: int) -> List[int]:
        # Convert k to array form: extract each digit
        nk = [ord(c) - ord('0') for c in str(k)]
        
        # Reverse both arrays for easier right-to-left processing
        a = num[::-1]  # Copy and reverse num
        b = nk[::-1]   # Copy and reverse nk
        
        # Ensure 'a' is the longer array for simplicity
        if len(a) < len(b):
            a, b = b, a
        
        na = len(a)
        nb = len(b)
        
        # Pad shorter array 'b' with zeros to match length
        b.extend([0] * (na - nb))
        
        # Perform digit-by-digit addition with carry
        ia = 0
        ib = 0
        carry = 0
        
        while ia < na:
            temp = a[ia] + b[ib] + carry
            carry = temp // 10  # Extract carry for next position
            temp %= 10          # Keep only the digit (0-9)
            a[ia] = temp        # Store result in array 'a'
            ia += 1
            ib += 1
        
        # Handle final carry if it exists
        if carry == 1:
            a.append(1)
        
        # Reverse back to get correct left-to-right order
        return a[::-1]
```

**Time Complexity**: O(max(len(num), len(str(k)))) - We process each digit once
**Space Complexity**: O(max(len(num), len(str(k)))) - For the arrays and result

**Key Insights**:
1. **Digit extraction**: `[ord(c) - ord('0') for c in str(k)]` converts integer k to digit array
2. **Carry handling**: `temp // 10` gives carry, `temp % 10` gives the digit to store  
3. **Array reversal**: Processing right-to-left is easier, but we need to reverse for correct output format
4. **Length normalization**: Padding shorter array with zeros simplifies the addition loop

# Tags

Array, Math, Addition, Carry, Digit Manipulation

