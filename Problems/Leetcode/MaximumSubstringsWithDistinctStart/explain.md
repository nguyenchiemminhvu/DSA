## Problem

https://leetcode.com/problems/maximum-substrings-with-distinct-start/description/

```
You are given a string s consisting of lowercase English letters.

Return an integer denoting the maximum number of substrings you can split s into such that 
each substring starts with a distinct character (i.e., no two substrings start with the same character).

Example 1:
Input: s = "abab"
Output: 2
Explanation: Split "abab" into "a" and "bab".
Each substring starts with a distinct character i.e 'a' and 'b'. Thus, the answer is 2.

Example 2:
Input: s = "abcd"
Output: 4
Explanation: Split "abcd" into "a", "b", "c", and "d".
Each substring starts with a distinct character. Thus, the answer is 4.

Example 3:
Input: s = "aaaa"
Output: 1
Explanation: All characters in "aaaa" are 'a'.
Only one substring can start with 'a'. Thus, the answer is 1.

Constraints:
- 1 <= s.length <= 10^5
- s consists of lowercase English letters.
```

## Observations

1. **Each substring must start with a distinct character** - This is the key constraint. No two substrings in our split can start with the same character.

2. **Maximum possible substrings** - Since each substring must start with a different character, the maximum number of substrings we can create is limited by the number of distinct characters in the string.

3. **Character frequency doesn't matter** - It doesn't matter how many times a character appears in the string. If a character exists, we can have at most one substring starting with it.

4. **Greedy observation** - We can always achieve the maximum by taking the smallest possible substring for each distinct character. For example, if we encounter 'a' for the first time, we can just take "a" as a substring, leaving the rest for other characters.

5. **The answer is always achievable** - For any string, we can always split it into exactly `k` substrings where `k` is the number of distinct characters. We just take each character's first occurrence as a separate substring (or group remaining characters into the last substring).

## Solution

```python
class Solution:
    def maxDistinct(self, s: str) -> int:
        return len(set(s))
```

**Approach: Count Distinct Characters**

The solution is elegantly simple: **the maximum number of substrings with distinct starting characters equals the number of distinct characters in the string**.

**Why this works:**
- Since each substring must start with a distinct character, we can have at most one substring per distinct character
- We can always achieve this maximum by greedily splitting the string
- One simple way: take each character's first occurrence as a single-character substring, continuing until we've used all distinct characters

**Time Complexity:** $O(n)$ where n is the length of the string
- Creating a set from the string requires scanning all characters once

**Space Complexity:** $O(k)$ where k is the number of distinct characters (at most 26 for lowercase English letters)
- The set stores at most 26 characters

**Example walkthrough:**
- `s = "abab"`: set(s) = {'a', 'b'}, len = 2
- `s = "abcd"`: set(s) = {'a', 'b', 'c', 'd'}, len = 4  
- `s = "aaaa"`: set(s) = {'a'}, len = 1

# Tags
#greedy #string #counting #easy

