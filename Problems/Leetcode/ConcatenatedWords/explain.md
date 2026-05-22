## Problem

https://leetcode.com/problems/concatenated-words/description

Given an array of strings `words` (without duplicates), return all the **concatenated words** in the given list of words.

A **concatenated word** is defined as a string that is comprised entirely of at least **two shorter words** (not necessarily distinct) in the given array.

### Examples

**Example 1:**
```
Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: 
- "catsdogcats" can be concatenated by "cats", "dog", and "cats"
- "dogcatsdog" can be concatenated by "dog", "cats", and "dog"
- "ratcatdogcat" can be concatenated by "rat", "cat", "dog", and "cat"
```

**Example 2:**
```
Input: words = ["cat","dog","catdog"]
Output: ["catdog"]
```

### Constraints

- `1 <= words.length <= 10^4`
- `1 <= words[i].length <= 30`
- `words[i]` consists of only lowercase English letters
- All strings in `words` are unique
- `1 <= sum(words[i].length) <= 10^5`

## Observations

1. **Key Insight**: A word is "concatenated" if it can be formed by combining at least 2 other words from the dictionary.

2. **Dynamic Programming/Memoization Approach**: For each word, we need to determine if it can be completely formed by concatenating shorter words from the dictionary.

3. **Word Set Lookup**: Store all words in a set for O(1) lookup time when checking if a substring is in the dictionary.

4. **Temporal Dependency**: When checking if a word can be formed, we must temporarily **remove** the word from the word_set. Otherwise, a word could form itself (e.g., "cat" + "cat" = "catcat" would be considered valid even if only one shorter word exists).

5. **Two Approaches**:
   - **Memoization (Top-Down DP)**: Recursive approach with memoization - check if substrings starting from position 0 can form the word
   - **Tabulation (Bottom-Up DP)**: Iterative approach - build up valid positions from the start

6. **Time Complexity**: 
   - For each word: O(n²) where n is the length of the word (checking all substrings)
   - Overall: O(m × n²) where m is the number of words, n is average word length

7. **Space Complexity**: O(m × n) for the word_set plus O(n) for the DP/memoization array

## Solution

### Memoization Approach (Provided Solution)

```python
class Solution:
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
        word_set = set(words)

        def can_form(word: str) -> bool:
            mem = {}
            def F(i: int) -> bool:
                """
                Check if word[0:i] can be formed by concatenating words from word_set.
                i: ending position in the word (exclusive)
                Returns: True if word[0:i] can be formed
                """
                if i < 0:
                    return False
                if i == 0:
                    return True  # Empty string is considered "formed"
                if i in mem:
                    return mem[i]
                
                res = False
                # Try all possible last words: word[j:i]
                for j in range(i):
                    sub = word[j:i]
                    if sub in word_set:
                        # If word[j:i] is a valid word AND word[0:j] can be formed
                        res = res or F(j)
                
                mem[i] = res
                return res
            
            return F(len(word))

        res = []
        for word in words:
            word_set.remove(word)  # Remove current word to avoid self-matching
            if can_form(word):
                res.append(word)
            word_set.add(word)  # Add it back for next iteration
        
        return res
```

### Alternative: Tabulation Approach (Bottom-Up DP)

```python
class Solution:
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
        word_set = set(words)

        def can_form(word: str) -> bool:
            # dp[i] = True if word[0:i] can be formed by concatenating words
            dp = [False] * (len(word) + 1)
            dp[0] = True  # Empty string can always be formed
            
            for i in range(1, len(word) + 1):
                for j in range(i):
                    if not dp[j]:
                        continue  # word[0:j] cannot be formed, skip
                    if word[j:i] in word_set:
                        dp[i] = True
                        break  # Found a valid partition, no need to check further
            
            return dp[len(word)]

        res = []
        for word in words:
            word_set.remove(word)  # Critical: avoid self-matching
            if can_form(word):
                res.append(word)
            word_set.add(word)  # Restore for next iteration
        
        return res
```

### Step-by-Step Walkthrough (Example: "catsdogcats")

1. Remove "catsdogcats" from word_set
2. Call `can_form("catsdogcats")`
3. Recursive calls with memoization:
   - `F(0)` → True (base case, empty string)
   - `F(3)` → True ("cat" is in word_set, F(0) is True)
   - `F(4)` → False ("c", "ca", "cat", "cats" at positions... "cats" ✓ but F(0) not considered yet)
   - Continue building up...
   - Eventually `F(12)` → True

### Key Points

1. **Why Remove the Word?**: If we don't remove it, a word like "cat" could be formed by "cat" alone, which violates the "at least 2 shorter words" requirement.

2. **Memoization vs Tabulation**: 
   - Memoization only computes needed states (top-down)
   - Tabulation computes all states (bottom-up, simpler to understand)
   - Both have same time/space complexity

3. **Optimization in Memoization**: Early termination with `res or F(j)` doesn't provide much benefit since we still check all positions. Could optimize by breaking early instead.

# Tags

- Dynamic Programming
- Memoization
- Backtracking
- Word Segmentation
- String Matching
- Hash Set

