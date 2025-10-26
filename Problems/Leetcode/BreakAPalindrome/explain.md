## Problem

https://leetcode.com/problems/break-a-palindrome/

```
Given a palindromic string of lowercase English letters palindrome, replace exactly one character with any lowercase English letter so that the resulting string is not a palindrome and that it is the lexicographically smallest one possible.

Return the resulting string. If there is no way to replace a character to make it not a palindrome, return an empty string.

A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, a has a character strictly smaller than the corresponding character in b. For example, "abcc" is lexicographically smaller than "abcd" because the first position they differ is at the fourth character, and 'c' is smaller than 'd'.

Example 1:

Input: palindrome = "abccba"
Output: "aaccba"
Explanation: There are many ways to make "abccba" not a palindrome, such as "zbccba", "aaccba", and "abacba".
Of all the ways, "aaccba" is the lexicographically smallest.

Example 2:

Input: palindrome = "a"
Output: ""
Explanation: There is no way to replace a single character to make "a" not a palindrome, so return an empty string.

Constraints:

1 <= palindrome.length <= 1000
palindrome consists of only lowercase English letters.
```

## Observations

1. **Edge Case**: If the palindrome has only 1 character, it's impossible to make it non-palindromic by changing exactly one character, so return empty string.

2. **Lexicographically Smallest Goal**: We want the lexicographically smallest non-palindrome. This means we should:
   - Change characters to 'a' when possible (since 'a' is the smallest letter)
   - Make changes as early (leftmost) as possible in the string

3. **Palindrome Property**: In a palindrome, characters are mirrored around the center. If we change a character on the left side, its mirror on the right would remain unchanged, breaking the palindrome.

4. **Special Case - All 'a's**: If the entire string consists of 'a's, we can't make it lexicographically smaller by changing any character to 'a'. In this case, we change the last character to 'b' to get the lexicographically smallest result.

5. **Strategy**: 
   - First, try to find the leftmost non-'a' character in the first half and change it to 'a'
   - If all characters in the first half are 'a', change the last character to 'b'

## Solution

1. **Handle Edge Case**: If length is 1, return empty string immediately.

2. **Convert to List**: Convert string to list for mutability.

3. **All 'a's Case**: If all characters are 'a', change the last character to 'b'. This ensures we get the lexicographically smallest non-palindrome.

4. **Find First Non-'a'**: Iterate through the first half of the string (left < right):
   - If we find a character that's not 'a', change it to 'a' and break
   - This gives us the lexicographically smallest result since we're changing the leftmost possible character to the smallest possible letter

5. **Fallback**: If no non-'a' character was found in the first half (meaning the first half is all 'a's), change the last character to 'b'.

**Time Complexity**: O(n) where n is the length of the string
**Space Complexity**: O(n) for the character list conversion

**Examples:**
- `"abccba"` → `"aaccba"` (change first 'b' to 'a')
- `"aabaa"` → `"aaaaa"` → `"aaaab"` (all 'a's case)
- `"racecar"` → `"aacecar"` (change first 'r' to 'a')

## Tags

array, string, greedy