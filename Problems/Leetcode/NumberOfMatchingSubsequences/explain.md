## Problem

https://leetcode.com/problems/number-of-matching-subsequences/description

Given a string `s` and an array of strings `words`, return the number of `words[i]` that is a **subsequence** of `s`.

A **subsequence** of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, `"ace"` is a subsequence of `"abcde"`.

**Example 1:**
```
Input: s = "abcde", words = ["a","bb","acd","ace"]
Output: 3
Explanation: Three strings in words are subsequences of s: "a", "acd", "ace"
```

**Example 2:**
```
Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
Output: 2
```

**Constraints:**
- `1 <= s.length <= 5*10^4`
- `1 <= words.length <= 5000`
- `1 <= words[i].length <= 50`
- `s` and `words[i]` consist of only lowercase English letters

## Observations

1. **Naive Two-Pointer Approach**: For each word, we can check if it's a subsequence of `s` by using two pointers—one on `s` and one on the word. If we find all characters of the word in order, it's a subsequence. This is **O(n*m)** where n = len(s), m = words.length * avg_word_length.

2. **Key Insight**: The bottleneck is repeatedly searching for the next occurrence of a character in `s`. Instead of searching linearly each time, we can precompute for every position in `s` and for every character (a-z), what is the next position where that character appears.

3. **Preprocessing Strategy**: Create a 2D DP table `dp[i][c]` where:
   - `i` is a position in string `s` (0 to n)
   - `c` is a character (a-z, represented as 0-25)
   - `dp[i][c]` stores the index of the next occurrence of character `c` starting from position `i`
   - Use a sentinel value (n) to indicate "no more occurrences"

4. **Backward Construction**: Build the DP table from right to left (from end of `s` to start). This allows us to:
   - Inherit previous values from `dp[i+1]`
   - Update the character we just encountered
   - Maintain correctness with O(n) time complexity

5. **Character Lookup**: For lowercase letters, use `ord(char) - ord('a')` to convert to index 0-25.

## Solution

### Approach: DP Preprocessing for Next Character Lookup

**Time Complexity**: O(n + m*k) where n = len(s), m = words.length, k = avg_word_length
- Preprocessing: O(26*n) = O(n)
- Checking all words: O(m*k*log(n)) amortized (binary search would be O(log n) per lookup)

**Space Complexity**: O(26*n) = O(n) for the DP table

```python
class Solution:
    def numMatchingSubseq(self, s: str, words: List[str]) -> int:
        n = len(s)
        
        # dp[i][c] -> next index where character c appears starting from position i
        # Initialize with n (sentinel value meaning "not found")
        dp = [[n] * 26 for _ in range(n + 1)]
        
        # Build DP table from right to left
        for i in range(n - 1, -1, -1):
            # Copy previous row (characters not yet updated)
            dp[i] = dp[i + 1][:]
            # Update the position of current character
            dp[i][ord(s[i]) - ord('a')] = i
        
        res = 0
        # Check each word if it's a subsequence
        for word in words:
            nw = len(word)
            i = 0  # Position in s
            iw = 0  # Position in word
            
            while i < n and iw < nw:
                # Find next position of word[iw] starting from position i
                found = dp[i][ord(word[iw]) - ord('a')]
                
                if found < n:  # Character found
                    iw += 1
                    i = found + 1  # Move to next position after found
                else:  # Character not found
                    break
            
            # If we matched all characters in word, it's a valid subsequence
            if iw == nw:
                res += 1
        
        return res
```

### Walkthrough Example

**Input:** s = "abcde", words = ["a","bb","acd","ace"]

**DP Table Construction:**
```
Position:  0  1  2  3  4  5(sentinel)
           a  b  c  d  e
dp[5]:    [5, 5, 5, 5, 5, ...] (all sentinel)
dp[4]:    [5, 5, 5, 5, 4, ...] (e at index 4)
dp[3]:    [5, 5, 5, 3, 4, ...] (d at index 3)
dp[2]:    [5, 5, 2, 3, 4, ...] (c at index 2)
dp[1]:    [5, 1, 2, 3, 4, ...] (b at index 1)
dp[0]:    [0, 1, 2, 3, 4, ...] (a at index 0)
```

**Checking "acd":**
- Start at i=0, iw=0
- Looking for 'a' at dp[0][0]=0 ✓, move to i=1, iw=1
- Looking for 'c' at dp[1][2]=2 ✓, move to i=3, iw=2
- Looking for 'd' at dp[3][3]=3 ✓, move to i=4, iw=3
- iw==3, so "acd" is a valid subsequence

**Checking "bb":**
- Start at i=0, iw=0
- Looking for 'b' at dp[0][1]=1 ✓, move to i=2, iw=1
- Looking for 'b' at dp[2][1]=5 (not found) ✗
- iw==1 < 2, so "bb" is NOT a valid subsequence

# Tags

Dynamic Programming, String, Two Pointers, Optimization

