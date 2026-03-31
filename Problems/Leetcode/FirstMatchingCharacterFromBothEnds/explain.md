## Problem

https://leetcode.com/problems/first-matching-character-from-both-ends/description/

Given a string `s` of length `n` consisting of lowercase English letters, find the smallest index `i` such that `s[i] == s[n - i - 1]` (the character at index `i` equals the character at the mirrored position from the end).

Return the smallest such index, or `-1` if no such index exists.

**Examples:**
- Input: `s = "abcacbd"` → Output: `1` (s[1]='b' == s[5]='b')
- Input: `s = "abc"` → Output: `1` (s[1]='b' == s[1]='b', indices coincide)
- Input: `s = "abcdab"` → Output: `-1` (no matching pair)

**Constraints:**
- 1 ≤ n ≤ 100
- s consists of lowercase English letters

## Observations

1. **Two-pointer approach**: We're comparing characters from opposite ends of the string moving inward.
2. **Index mapping**: For any index `i`, the mirrored index from the end is `n - i - 1`.
3. **The search space**: We only need to check up to the middle of the string. When `i` reaches the center, `n - i - 1` will equal or cross `i`.
4. **First match is smallest**: Since we iterate from `i = 0` upward, the first match we find is guaranteed to be the smallest valid index.
5. **Linear time complexity**: A single pass through the relevant portion of the string is sufficient.

## Solution

```python
class Solution:
    def firstMatchingIndex(self, s: str) -> int:
        n = len(s)
        for i in range(n):
            if s[i] == s[n - i - 1]:
                return i
        return -1
```

**Algorithm Explanation:**

1. Store the length of the string in `n` for efficient access.
2. Iterate through indices from `0` to `n-1`:
   - For each index `i`, calculate the mirrored index `n - i - 1`.
   - Compare the character at position `i` with the character at position `n - i - 1`.
   - If they match, immediately return `i` (this is the smallest index due to forward iteration).
3. If no matching pair is found after checking all indices, return `-1`.

**Time Complexity:** O(n) — single pass through the string  
**Space Complexity:** O(1) — only using a constant amount of extra space

# Tags

