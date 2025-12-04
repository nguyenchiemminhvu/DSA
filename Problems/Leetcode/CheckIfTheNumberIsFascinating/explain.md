## Problem

https://leetcode.com/problems/check-if-the-number-is-fascinating/description/

```
You are given an integer n that consists of exactly 3 digits.

We call the number n fascinating if, after the following modification, the resulting number 
contains all the digits from 1 to 9 exactly once and does not contain any 0's:

- Concatenate n with the numbers 2 * n and 3 * n.

Return true if n is fascinating, or false otherwise.

Concatenating two numbers means joining them together. For example, the concatenation of 121 and 371 is 121371.

Example 1:
Input: n = 192
Output: true
Explanation: We concatenate the numbers n = 192 and 2 * n = 384 and 3 * n = 576. 
The resulting number is 192384576. This number contains all the digits from 1 to 9 exactly once.

Example 2:
Input: n = 100
Output: false
Explanation: We concatenate the numbers n = 100 and 2 * n = 200 and 3 * n = 300. 
The resulting number is 100200300. This number does not satisfy any of the conditions.

Constraints:
100 <= n <= 999
```

## Observations

1. **Input Range**: Since `n` is a 3-digit number (100 ≤ n ≤ 999), we have:
   - `n`: 3 digits
   - `2 * n`: 3-4 digits (200 to 1998)
   - `3 * n`: 3-4 digits (300 to 2997)
   - Concatenated string: 9-11 characters total

2. **Fascinating Number Requirements**:
   - Must contain digits 1-9 exactly once each
   - Cannot contain any 0's
   - Total of 9 unique non-zero digits

3. **Key Insights**:
   - If any of n, 2*n, or 3*n contains a '0', the number cannot be fascinating
   - The concatenated string must have exactly 9 characters (since we need 1-9 exactly once)
   - All digits must be unique (no duplicates)
   - The set of digits must exactly match {1, 2, 3, 4, 5, 6, 7, 8, 9}

## Solution

1. **Concatenation**: 
   - Convert `n`, `2*n`, and `3*n` to strings and concatenate them
   - Example: n=192 → "192" + "384" + "576" = "192384576"

2. **Check for Zeros**:
   - Iterate through each character in the concatenated string
   - If we find a '0', immediately return `False`
   - Otherwise, collect all digits in an array

3. **Validate Uniqueness and Completeness**:
   - Create a set from the collected digits
   - Check two conditions:
     - `len(ss) == len(arr)`: Ensures all digits are unique (no duplicates)
     - `ss == set('123456789')`: Ensures we have exactly the digits 1-9

**Time Complexity**: O(1)
- The concatenated string has a fixed maximum length (at most 11 characters)
- All operations (string concatenation, iteration, set creation) are constant time

**Space Complexity**: O(1)
- We use a fixed amount of space (array and set with at most 11 elements)

**Alternative Approach (More Concise)**:

```python
class Solution:
    def isFascinating(self, n: int) -> bool:
        s = str(n) + str(2 * n) + str(3 * n)
        return '0' not in s and len(s) == 9 and set(s) == set('123456789')
```

This approach is more concise:
- Check if '0' is not in the string
- Verify the length is exactly 9 (since we need exactly 9 unique digits)
- Confirm the set of digits matches {1, 2, 3, 4, 5, 6, 7, 8, 9}

# Tags

#Math #String #HashSet #Simulation

