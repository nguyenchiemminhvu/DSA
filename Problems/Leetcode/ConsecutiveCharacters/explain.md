## Problem

https://leetcode.com/problems/consecutive-characters/description/

The power of the string is the maximum length of a non-empty substring that contains only one unique character.

Given a string s, return the power of s.

**Example 1:**
- Input: s = "leetcode"
- Output: 2
- Explanation: The substring "ee" is of length 2 with the character 'e' only.

**Example 2:**
- Input: s = "abbcccddddeeeeedcba"
- Output: 5
- Explanation: The substring "eeeee" is of length 5 with the character 'e' only.

**Constraints:**
- 1 <= s.length <= 500
- s consists of only lowercase English letters.

## Observations

1. We need to find the longest consecutive sequence of identical characters
2. We can iterate through the string once, keeping track of:
   - Current consecutive count
   - Maximum count seen so far
   - Previous character to compare with current
3. When we encounter the same character as previous, increment count
4. When we encounter a different character, reset count to 1
5. Always update the maximum result when count increases

## Solution

**Algorithm:**
1. Initialize `res = 1` (minimum power is 1 since string is non-empty)
2. Initialize `count = 1` and `prev = '#'` (dummy character)
3. For each character in the string:
   - If current character equals previous character:
     - Increment count (we found another consecutive character)
     - Update result with maximum of current result and count
   - Else:
     - Reset count to 1 (start new consecutive sequence)
   - Update prev to current character
4. Return the maximum power found

**Time Complexity:** O(n) - single pass through the string
**Space Complexity:** O(1) - only using constant extra space

# Tags
- String
- Two Pointers
- Sliding Window

