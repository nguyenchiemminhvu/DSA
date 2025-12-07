## Problem

https://leetcode.com/problems/find-special-substring-of-length-k/description/

```
You are given a string s and an integer k.

Determine if there exists a substring of length exactly k in s that satisfies the following conditions:

1. The substring consists of only one distinct character (e.g., "aaa" or "bbb").
2. If there is a character immediately before the substring, it must be different from the character in the substring.
3. If there is a character immediately after the substring, it must also be different from the character in the substring.

Return true if such a substring exists. Otherwise, return false.

Example 1:
Input: s = "aaabaaa", k = 3
Output: true
Explanation:
The substring s[4..6] == "aaa" satisfies the conditions.
- It has a length of 3.
- All characters are the same.
- The character before "aaa" is 'b', which is different from 'a'.
- There is no character after "aaa".

Example 2:
Input: s = "abc", k = 2
Output: false
Explanation:
There is no substring of length 2 that consists of one distinct character and satisfies the conditions.

Constraints:
- 1 <= k <= s.length <= 100
- s consists of lowercase English letters only.
```

## Observations

1. **Substring Requirements**: We need to find a substring of exactly length k where:
   - All characters are the same (only one distinct character)
   - The character before (if exists) is different
   - The character after (if exists) is different

2. **Edge Cases**:
   - If the substring starts at index 0, there's no character before it
   - If the substring ends at the last position, there's no character after it
   - We only need to check boundaries that exist

3. **Brute Force Approach**: Since the string length is at most 100, we can check every possible substring of length k.

4. **Key Insight**: We're looking for a "run" of identical characters that is exactly k characters long and is isolated from other occurrences of the same character.

## Solution

**Approach**: Sliding Window with Validation

**Algorithm**:
1. Iterate through all possible starting positions (from 0 to n - k)
2. For each position i, extract the substring of length k
3. Check if the substring meets all three conditions:
   - **Single Character Check**: Use `set(sub)` to verify all characters are the same
   - **Left Boundary Check**: If i > 0, ensure `s[i-1]` differs from the substring character
   - **Right Boundary Check**: If i + k < n, ensure `s[i+k]` differs from the substring character
4. Return `True` immediately when a valid substring is found
5. Return `False` if no valid substring exists after checking all positions

**Time Complexity**: O(n * k) where n is the length of the string
- We iterate through n - k + 1 positions
- For each position, we create a substring (O(k)) and check if it has one distinct character (O(k))

**Space Complexity**: O(k) for storing the substring and the set

**Example Walkthrough** (s = "aaabaaa", k = 3):
- i=0: sub="aaa", no left boundary, right boundary s[3]='b' ≠ 'a' ✓ → Returns `True`

**Example Walkthrough** (s = "abc", k = 2):
- i=0: sub="ab", has 2 distinct characters → skip
- i=1: sub="bc", has 2 distinct characters → skip
- Returns `False`

# Tags
`String` `Sliding Window` `Two Pointers`

