## Problem

https://leetcode.com/problems/maximum-value-of-a-string-in-an-array/

```
The value of an alphanumeric string can be defined as:

The numeric representation of the string in base 10, if it comprises of digits only.
The length of the string, otherwise.
Given an array strs of alphanumeric strings, return the maximum value of any string in strs.

Example 1:

Input: strs = ["alic3","bob","3","4","00000"]
Output: 5
Explanation: 
- "alic3" consists of both letters and digits, so its value is its length, i.e. 5.
- "bob" consists only of letters, so its value is also its length, i.e. 3.
- "3" consists only of digits, so its value is its numeric equivalent, i.e. 3.
- "4" also consists only of digits, so its value is 4.
- "00000" consists only of digits, so its value is 0.
Hence, the maximum value is 5, of "alic3".

Example 2:

Input: strs = ["1","01","001","0001"]
Output: 1
Explanation: 
Each string in the array has value 1. Hence, we return 1.

Constraints:

1 <= strs.length <= 100
1 <= strs[i].length <= 9
strs[i] consists of only lowercase English letters and digits.
```

## Observations

1. **Two Types of String Values**:
   - **Numeric strings** (digits only): Value = numeric representation (e.g., "123" → 123, "00000" → 0)
   - **Alphanumeric strings** (contains letters): Value = string length (e.g., "alic3" → 5, "bob" → 3)

2. **Key Insight**: We need to distinguish between strings that are purely numeric vs. strings that contain letters.

3. **Edge Cases**:
   - Leading zeros: "00000" is still a valid numeric string with value 0
   - Single digits: "3" has numeric value 3, not length 1
   - Mixed content: "alic3" contains letters, so we use length (5), not attempt to parse as number

4. **Algorithm Strategy**:
   - Try to convert each string to integer
   - If successful (no ValueError), use the numeric value
   - If conversion fails (contains letters), use the string length
   - Keep track of maximum value seen so far

5. **Time Complexity**: O(n × m) where n is number of strings, m is average string length (for int parsing)
6. **Space Complexity**: O(1) - only storing the result variable

## Solution

1. **Initialize**: `res = 0` to track maximum value found
2. **Iterate**: Through each string in the array
3. **Try conversion**: Attempt `int(s)` to check if string is purely numeric
   - **Success**: String contains only digits → use numeric value
   - **ValueError exception**: String contains letters → use string length
4. **Update maximum**: `res = max(res, current_value)` for each string
5. **Return**: The maximum value found

**Example walkthrough with strs = ["alic3","bob","3","4","00000"]**:
- "alic3": int() raises ValueError → use len("alic3") = 5, res = max(0, 5) = 5
- "bob": int() raises ValueError → use len("bob") = 3, res = max(5, 3) = 5  
- "3": int("3") = 3 → use numeric value 3, res = max(5, 3) = 5
- "4": int("4") = 4 → use numeric value 4, res = max(5, 4) = 5
- "00000": int("00000") = 0 → use numeric value 0, res = max(5, 0) = 5

**Why this approach is elegant**:
- **Exception handling** naturally distinguishes the two cases
- **No manual character checking** needed (int() does it for us)
- **Handles edge cases** like leading zeros automatically
- **Clean and readable** code structure

# Tags

Array, String, Exception Handling

