## Problem

https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/description/

```
Given the binary representation of an integer as a string s, return the number of steps to reduce it to 1 under the following rules:

- If the current number is even, you have to divide it by 2.
- If the current number is odd, you have to add 1 to it.

It is guaranteed that you can always reach one for all test cases.

Example 1:
Input: s = "1101"
Output: 6
Explanation: "1101" corresponds to number 13 in their decimal representation.
Step 1) 13 is odd, add 1 and obtain 14. 
Step 2) 14 is even, divide by 2 and obtain 7.
Step 3) 7 is odd, add 1 and obtain 8.
Step 4) 8 is even, divide by 2 and obtain 4.  
Step 5) 4 is even, divide by 2 and obtain 2. 
Step 6) 2 is even, divide by 2 and obtain 1.

Example 2:
Input: s = "10"
Output: 1
Explanation: "10" corresponds to number 2 in their decimal representation.
Step 1) 2 is even, divide by 2 and obtain 1.

Example 3:
Input: s = "1"
Output: 0

Constraints:
- 1 <= s.length <= 500
- s consists of characters '0' or '1'
- s[0] == '1'
```

## Observations

1. **Binary Operations Insight**:
   - Dividing by 2 in binary is equivalent to a right shift operation (`>> 1`)
   - Checking if a number is odd can be done by checking the least significant bit (`val & 1`)
   - Adding 1 to an odd number makes it even

2. **Bit-Level Understanding**:
   - If the last bit is `0`, the number is even → right shift (remove last bit)
   - If the last bit is `1`, the number is odd → add 1 (which will create a carry)

3. **Simplification**:
   - Instead of manipulating the string directly, convert it to an integer
   - Use bitwise operations for efficiency

4. **Edge Case**:
   - When `s = "1"`, the number is already 1, so return 0 steps

## Solution

### Approach: Direct Simulation with Bitwise Operations

The solution uses a straightforward simulation approach:

```python
class Solution:
    def numSteps(self, s: str) -> int:
        val = int(s, 2)  # Convert binary string to integer
        steps = 0
        while val > 1:
            if val & 1:  # Check if odd (last bit is 1)
                val += 1
            else:        # Even (last bit is 0)
                val >>= 1  # Right shift (divide by 2)
            steps += 1
        return steps
```

**How it works**:

1. **Convert binary string to integer**: `int(s, 2)` converts the binary string to its decimal equivalent
   
2. **Check parity**: `val & 1` performs a bitwise AND with 1, which returns:
   - `1` if the number is odd (last bit is 1)
   - `0` if the number is even (last bit is 0)

3. **Apply operations**:
   - If odd: add 1 to make it even
   - If even: right shift by 1 bit (equivalent to dividing by 2)

4. **Count steps**: Increment the counter after each operation

5. **Termination**: Stop when `val` becomes 1

**Time Complexity**: O(log n) where n is the decimal value of the binary number. Each operation either adds 1 or divides by 2, so the number reduces logarithmically.

**Space Complexity**: O(1) - only using a constant amount of extra space.

**Example walkthrough** for `s = "1101"` (13 in decimal):
- Step 0: val = 13 (1101), odd → val = 14 (1110)
- Step 1: val = 14 (1110), even → val = 7 (111)
- Step 2: val = 7 (111), odd → val = 8 (1000)
- Step 3: val = 8 (1000), even → val = 4 (100)
- Step 4: val = 4 (100), even → val = 2 (10)
- Step 5: val = 2 (10), even → val = 1 (1)
- Total: 6 steps

# Tags
`Binary`, `Bit Manipulation`, `Simulation`, `Math`

