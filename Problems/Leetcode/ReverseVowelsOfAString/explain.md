## Problem

https://leetcode.com/problems/reverse-vowels-of-a-string/description/

```
Given a string s, reverse only all the vowels in the string and return it.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.

Example 1:

Input: s = "IceCreAm"

Output: "AceCreIm"

Explanation:

The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".

Example 2:

Input: s = "leetcode"

Output: "leotcede"

Constraints:

1 <= s.length <= 3 * 105
s consist of printable ASCII characters.
```

## Observations

1. **Vowel Definition**: The problem considers both uppercase and lowercase vowels: 'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'.

2. **Only Vowels Need Reversal**: We need to reverse only the vowels while keeping consonants in their original positions.

3. **Position Tracking**: We need to identify all vowel positions first, then swap them from both ends.

4. **Two-Pointer Approach**: Since we need to reverse vowels, we can use a two-pointer technique on the vowel positions.

5. **String Mutability**: Since strings are immutable in Python, we need to convert to a list for in-place modifications.

## Solution

**Approach**: Position Collection + Two Pointers

The solution uses a two-step approach:

1. **Collection Phase**: 
   - Convert string to list for mutability
   - Iterate through the string and collect indices of all vowel characters
   - Store these indices in a temporary array

2. **Reversal Phase**:
   - Use two pointers (left and right) on the vowel indices array
   - Swap characters at vowel positions from both ends moving inward
   - Continue until pointers meet or cross

**Time Complexity**: O(n) where n is the length of the string
- First pass to collect vowel positions: O(n)
- Second pass to swap vowels: O(k) where k is number of vowels
- Overall: O(n)

**Space Complexity**: O(n) 
- O(n) for converting string to list
- O(k) for storing vowel indices where k ≤ n

**Algorithm Steps**:
1. Define vowel set as 'AEIOUaeiou'
2. Convert input string to list
3. Collect all vowel positions in temp array
4. Use two pointers to swap vowels from ends
5. Convert list back to string and return

**Example Walkthrough** (`s = "hello"`):
- Initial: ['h', 'e', 'l', 'l', 'o']
- Vowel positions: [1, 4] (indices of 'e' and 'o')
- Swap s[1] and s[4]: ['h', 'o', 'l', 'l', 'e']
- Result: "holle"

## Tags

array, string, two pointers