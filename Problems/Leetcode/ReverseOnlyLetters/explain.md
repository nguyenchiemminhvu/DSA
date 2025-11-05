## Problem

https://leetcode.com/problems/reverse-only-letters/

```
Given a string s, reverse the string according to the following rules:

All the characters that are not English letters remain in the same position.
All the English letters (lowercase or uppercase) should be reversed.
Return s after reversing it.

Example 1:

Input: s = "ab-cd"
Output: "dc-ba"

Example 2:

Input: s = "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"

Example 3:

Input: s = "Test1ng-Leet=code-Q!"
Output: "Qedo1ct-eeLg=ntse-T!"

Constraints:

1 <= s.length <= 100
s consists of characters with ASCII values in the range [33, 122].
s does not contain '\"' or '\\'.
```

## Observations

1. **Problem Requirements**:
   - Reverse only English letters (both uppercase and lowercase)
   - Non-letter characters (digits, symbols, spaces) must remain in their original positions
   - The reversed letters should occupy the same letter positions but in reverse order

2. **Key Insights**:
   - This is a **selective reversal** problem - we only reverse specific characters (letters)
   - Non-letter characters act as "anchors" that stay in place
   - We need to identify letter positions and reverse only those characters

3. **Pattern Analysis**:
   - Extract all letters from the string while preserving their order
   - Reverse the extracted letters
   - Place the reversed letters back into their original letter positions
   - Leave non-letter characters untouched

4. **Algorithm Strategy**:
   - **Two-pass approach**: First pass extracts letters, second pass places them back
   - **Character classification**: Use `string.ascii_letters` or equivalent to identify letters
   - **In-place replacement**: Replace letters while preserving non-letter character positions

5. **Edge Cases**:
   - String with no letters → return original string
   - String with only letters → simple string reversal
   - String with only non-letters → return original string
   - Mixed case letters → reverse preserves original case of each letter

## Solution

**Approach**: Extract letters, reverse them, then place back in letter positions

**Algorithm**:
1. **Extract Letters**: Iterate through the string and collect all English letters into a temporary list
2. **Reverse Letters**: Reverse the temporary list to get letters in reverse order
3. **Reconstruct String**: 
   - Convert original string to a mutable list
   - Use an iterator to traverse the reversed letters
   - For each position in the original string:
     - If it's a letter position, replace with next letter from reversed list
     - If it's a non-letter, keep original character
4. **Return Result**: Join the modified list back into a string

**Implementation Details**:
- Uses `string.ascii_uppercase + string.ascii_lowercase` to create a set of all English letters
- Creates a temporary list to store extracted letters
- Uses `temp.reverse()` to reverse the letters in-place
- Uses an iterator `it` to track position in the reversed letters list
- Converts string to list for mutable operations, then joins back to string

**Example Walkthrough**:
```
Input: s = "a-bC-dEf-ghIj"

Step 1: Extract letters
letters = ['a', 'b', 'C', 'd', 'E', 'f', 'g', 'h', 'I', 'j']

Step 2: Reverse letters  
reversed_letters = ['j', 'I', 'h', 'g', 'f', 'E', 'd', 'C', 'b', 'a']

Step 3: Place back in letter positions
Original: ['a', '-', 'b', 'C', '-', 'd', 'E', 'f', '-', 'g', 'h', 'I', 'j']
Result:   ['j', '-', 'I', 'h', '-', 'g', 'f', 'E', '-', 'd', 'C', 'b', 'a']

Final: "j-Ih-gfE-dCba"
```

**Time Complexity**: O(n) where n is the length of the string
- First pass: O(n) to extract letters
- Reverse operation: O(k) where k is number of letters 
- Second pass: O(n) to reconstruct string
- Overall: O(n)

**Space Complexity**: O(n)
- O(k) for temporary letters list where k ≤ n
- O(n) for converting string to list
- Overall: O(n)

**Alternative Approaches**:
- **Two-pointer technique**: Use left and right pointers to swap letters directly without extra storage
- **Stack-based**: Push letters onto stack, then pop them back into letter positions

# Tags

String, Two Pointers, Array Manipulation, Character Processing

