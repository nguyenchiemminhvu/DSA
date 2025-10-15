## Problem

https://leetcode.com/problems/maximum-69-number/description/

```
You are given a positive integer num consisting only of digits 6 and 9.

Return the maximum number you can get by changing at most one digit (6 becomes 9, and 9 becomes 6).

Example 1:

Input: num = 9669
Output: 9969
Explanation: 
Changing the first digit results in 6669.
Changing the second digit results in 9969.
Changing the third digit results in 9699.
Changing the fourth digit results in 9666.
The maximum number is 9969.

Example 2:

Input: num = 9996
Output: 9999
Explanation: Changing the last digit 6 to 9 results in the maximum number.

Example 3:

Input: num = 9999
Output: 9999
Explanation: It is better not to apply any change.

Constraints:

1 <= num <= 104
num consists of only 6 and 9 digits.
```

## Observations

1. **Goal**: Maximize the number by changing at most one digit
2. **Key insight**: To maximize a number, we want to make the leftmost (most significant) digit as large as possible
3. **Strategy**: Find the first occurrence of '6' from left to right and change it to '9'
4. **Edge case**: If there are no '6's in the number, don't change anything (the number is already maximum)
5. **Why leftmost '6'?**: Changing a digit at position i has more impact than changing a digit at position j where i < j (more significant position)

**Example walkthrough**:
- For 9669: The first '6' is at position 1 (0-indexed), changing it gives 9969 (maximum possible)
- For 9996: The first '6' is at position 3, changing it gives 9999
- For 9999: No '6' exists, so no change needed

## Solution

1. **`reverse_num(val)`**: Reverses the digits of the input number
   - Processes digits from right to left (least significant to most significant)
   - Builds the reversed number digit by digit

2. **`reverse_and_replace(val)`**: Processes the reversed number and replaces the first '6' encountered
   - Uses a flag `k=1` to ensure only one replacement
   - When it finds a '6' and `k > 0`, it changes the digit to '9' and decrements `k`
   - Builds the result number while processing

3. **Main logic**: 
   - First reverses the original number
   - Then processes the reversed number to find and replace the first '6'
   - The "first '6'" in the reversed number corresponds to the **rightmost '6'** in the original number

### Why this approach works:
- By reversing first, we process digits from right to left in the original number
- When we find the first '6' in the reversed number, it's actually the **rightmost '6'** in the original
- However, there's a subtle issue: this finds the rightmost '6', not the leftmost one!

### More Direct Approach:
```python
class Solution:
    def maximum69Number(self, num: int) -> int:
        # Convert to string for easy manipulation
        s = str(num)
        # Find first occurrence of '6' and replace with '9'
        return int(s.replace('6', '9', 1))
```

### Time Complexity: O(d) where d is the number of digits
### Space Complexity: O(1) for the reverse approach, O(d) for string approach

## Tags

math