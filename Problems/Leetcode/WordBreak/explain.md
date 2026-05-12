## Problem

https://leetcode.com/problems/word-break/description

Given a string `s` and a dictionary of strings `wordDict`, determine if `s` can be segmented into a space-separated sequence of one or more dictionary words.

**Key Points:**
- The same word in the dictionary may be reused multiple times in the segmentation
- All dictionary words are unique
- Only lowercase English letters are used

**Constraints:**
- 1 ≤ s.length ≤ 300
- 1 ≤ wordDict.length ≤ 1000
- 1 ≤ wordDict[i].length ≤ 20

**Examples:**
1. Input: s = "leetcode", wordDict = ["leet","code"] → Output: true ("leet code")
2. Input: s = "applepenapple", wordDict = ["apple","pen"] → Output: true ("apple pen apple")
3. Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"] → Output: false (no valid segmentation)

## Observations

1. **Decision Problem Structure**: At each position in the string, we need to decide if we can form a valid segmentation from that position to the end. This is inherently a yes/no decision that suggests DP or recursion with memoization.

2. **Overlapping Subproblems**: Multiple positions may need to check if the remaining string can be segmented. For example, in "applepennapple", both positions after "apple" and after the second "apple" ask the same question about the remaining string. This is a sign of optimal substructure.

3. **Dependency Direction**: We can solve this either:
   - **Top-down (memoization)**: From position 0, try each word and recursively check if we can segment the rest
   - **Bottom-up (DP)**: Work backwards from the end of the string; mark positions that can successfully segment the remaining substring

4. **State Definition**: `dp[i]` = true if the substring `s[0:i]` can be segmented into dictionary words. The answer is `dp[n]`.

5. **Transition Logic**: For each position `i` going backwards, check if there exists a word in the dictionary that:
   - Starts at position `i` (i.e., `s[i:i+len(word)] == word`)
   - AND the rest after this word can be segmented (`dp[i + len(word)] == true`)

6. **Array Sizing**: The DP array is sized to `n + 1001` (with 1001 buffer) to avoid index out-of-bounds when checking `dp[i + word_length]` in the worst case where words can be up to 20 characters and string up to 300.

## Solution

**Algorithm: Dynamic Programming (Bottom-Up)**

```python
def wordBreak(self, s: str, words: List[str]) -> bool:
    n = len(s)
    
    # dp[i] = True if s[0:i] can be segmented using words
    dp = [False] * (n + 1001)
    dp[n] = True  # Empty string can always be segmented
    
    # Work backwards from position n-1 to 0
    for i in range(n - 1, -1, -1):
        for word in words:
            word_len = len(word)
            # Check if a word matches at position i and rest can be segmented
            if dp[i + word_len] and s[i:i + word_len] == word:
                dp[i] = True
    
    return dp[0]
```

**Key Steps:**

1. **Base Case**: `dp[n] = True` because an empty remaining string is always valid.

2. **Iteration**: Loop from position `n-1` down to `0`.

3. **Word Matching**: For each position `i`, try every word in the dictionary:
   - Extract substring `s[i:i+word_len]`
   - If it matches the word AND `dp[i + word_len]` is true, mark `dp[i] = True`
   - Once `dp[i]` is set to true, we can break early (optimization)

4. **Answer**: Return `dp[0]` which tells us if the entire string starting from position 0 can be segmented.

**Time Complexity**: O(n² × m) where n is the length of s and m is the average length of words (we check m words at each of n positions, each check involves string comparison).

**Space Complexity**: O(n) for the DP array.

**Alternative Approach (Commented)**: The commented code shows a top-down memoized recursion approach:
- Start from position 0
- Try each word, if it matches, recursively check the remaining substring
- Use memoization to cache results for positions already computed
- Both approaches have similar complexity but bottom-up DP can be more efficient due to iterative execution

# Tags

`Dynamic Programming`, `String`, `Memoization`, `Tabulation`