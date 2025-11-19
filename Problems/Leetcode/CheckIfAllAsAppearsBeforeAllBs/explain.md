## Problem

https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/description/

```
Given a string s consisting of only the characters 'a' and 'b', return true if every 'a' appears before every 'b' in the string. Otherwise, return false.

Example 1:

Input: s = "aaabbb"
Output: true
Explanation:
The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4, and 5.
Hence, every 'a' appears before every 'b' and we return true.

Example 2:

Input: s = "abab"
Output: false
Explanation:
There is an 'a' at index 2 and a 'b' at index 1.
Hence, not every 'a' appears before every 'b' and we return false.

Example 3:

Input: s = "bbb"
Output: true
Explanation:
There are no 'a's, hence, every 'a' appears before every 'b' and we return true.

Constraints:

1 <= s.length <= 100
s[i] is either 'a' or 'b'.
```

## Observations

1. **Problem Understanding**: We need to check if all 'a' characters appear before all 'b' characters in the string.

2. **Key Insight**: Once we encounter the first 'b', we should never see another 'a' for the condition to be satisfied.

3. **Invalid Pattern**: The pattern "ba" anywhere in the string would make the answer false, as it means there's an 'a' after a 'b'.

4. **Edge Cases**:
   - String with only 'a's: Valid (no 'b's to violate the condition)
   - String with only 'b's: Valid (no 'a's to violate the condition)
   - Empty string: Valid by definition

5. **Valid Patterns**: The string should follow the pattern `a*b*` (zero or more 'a's followed by zero or more 'b's).

## Solution

1. **State Tracking**: Use `count_b` to track if we've seen any 'b' characters.
   
2. **Scanning Logic**: 
   - When we encounter a 'b', increment the counter (marking that we've seen at least one 'b')
   - When we encounter an 'a', check if we've already seen any 'b's:
     - If `count_b > 0`, it means we've seen a 'b' before this 'a', which violates the condition
     - Return `False` immediately

3. **Final Result**: If we complete the scan without finding any 'a' after a 'b', return `True`.

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(1) - only using a constant amount of extra space

**Alternative Approach**: We could also solve this by checking if the string matches the pattern `a*b*` or by finding the last occurrence of 'a' and first occurrence of 'b' and ensuring last_a_index < first_b_index.

# Tags

String, Simulation, Pattern Matching

