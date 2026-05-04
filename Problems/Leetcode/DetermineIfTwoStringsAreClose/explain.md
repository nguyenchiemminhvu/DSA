## Problem

https://leetcode.com/problems/determine-if-two-strings-are-close/description

Two strings are considered **close** if you can attain one from the other using the following operations:

- **Operation 1**: Swap any two existing characters.
  - Example: `abcde` → `aecdb`
  
- **Operation 2**: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
  - Example: `aacabb` → `bbcbaa` (all `a`'s turn into `b`'s, and all `b`'s turn into `a`'s)

You can use the operations on either string as many times as necessary.

**Task**: Given two strings `word1` and `word2`, return `true` if `word1` and `word2` are close, and `false` otherwise.

### Examples

**Example 1:**
- Input: `word1 = "abc"`, `word2 = "bca"`
- Output: `true`
- Explanation: You can attain `word2` from `word1` in 2 operations.
  - Apply Operation 1: `"abc"` → `"acb"`
  - Apply Operation 1: `"acb"` → `"bca"`

**Example 2:**
- Input: `word1 = "a"`, `word2 = "aa"`
- Output: `false`
- Explanation: It is impossible to attain `word2` from `word1`, or vice versa, in any number of operations.

**Example 3:**
- Input: `word1 = "cabbba"`, `word2 = "abbccc"`
- Output: `true`
- Explanation: You can attain `word2` from `word1` in 3 operations.
  - Apply Operation 1: `"cabbba"` → `"caabbb"`
  - Apply Operation 2: `"caabbb"` → `"baaccc"`
  - Apply Operation 2: `"baaccc"` → `"abbccc"`

### Constraints

- `1 <= word1.length, word2.length <= 10^5`
- `word1` and `word2` contain only lowercase English letters

---

## Observations

1. **Operation 1 (Swap)**: Allows us to rearrange characters in any order. This means we can place any character at any position without worrying about order.

2. **Operation 2 (Transform)**: Allows us to exchange the identities of two characters. For example, if we have characters `a` and `b`, we can swap all occurrences of `a` with `b` and vice versa.

3. **Key Insight**: 
   - Operation 1 tells us that **the order of characters doesn't matter** — we only care about what characters exist and their frequencies.
   - Operation 2 tells us that **we can rearrange the frequency mapping**. If `word1` has frequencies `[1, 2, 3]` for some characters and `word2` has frequencies `[1, 2, 3]` for potentially different characters, we can transform one into the other.

4. **Necessary Conditions**:
   - Both strings must have the **same length** (we can't add or remove characters)
   - Both strings must contain the **same set of characters** (Operation 2 can only swap characters that exist in the string)
   - Both strings must have **the same frequency distribution** (when sorted), because Operation 2 allows us to reassign which character has which frequency

5. **Sufficient Conditions**: If all three conditions above are met, we can always transform one string into the other:
   - Use Operation 2 to rearrange frequencies among the characters
   - Use Operation 1 to rearrange the order

---

## Solution

### Approach: Character Set and Frequency Distribution

The solution leverages the observations above:

1. **Check Length**: If the strings have different lengths, they can never be close.

2. **Check Character Set**: If the two strings don't have the same set of characters, Operation 2 cannot help us because it can only swap existing characters.

3. **Check Frequency Distribution**: Sort the frequency counts of both strings. If the sorted frequency lists are identical, we can always rearrange one string to match the other using the two operations.

### Algorithm

```python
from collections import Counter

class Solution:
    def closeStrings(self, s1: str, s2: str) -> bool:
        # Condition 1: Check if lengths are equal
        if len(s1) != len(s2):
            return False
        
        # Condition 2: Check if both strings have the same set of characters
        if set(s1) != set(s2):
            return False
        
        # Condition 3: Check if frequency distributions are the same
        freq1 = Counter(s1)
        freq2 = Counter(s2)
        
        # Sort the frequency values
        sorted_freq1 = sorted(freq1.values())
        sorted_freq2 = sorted(freq2.values())
        
        # If sorted frequencies are equal, strings are close
        return sorted_freq1 == sorted_freq2
```

### Complexity Analysis

- **Time Complexity**: $O(n + 26 \log 26) = O(n)$
  - Counting characters: $O(n)$
  - Comparing sets: $O(26) = O(1)$ (at most 26 lowercase letters)
  - Sorting frequencies: $O(26 \log 26) = O(1)$ (at most 26 different characters)
  
- **Space Complexity**: $O(1)$
  - At most 26 entries in the Counter (one for each lowercase letter)
  - The character sets are also bounded by 26

### Why This Works: Detailed Explanation

**Example 3 Walkthrough**: `word1 = "cabbba"`, `word2 = "abbccc"`

1. **Length Check**: Both have length 6 ✓

2. **Character Set Check**:
   - Characters in `word1`: {`a`, `b`, `c`}
   - Characters in `word2`: {`a`, `b`, `c`}
   - Same sets ✓

3. **Frequency Distribution**:
   - `word1` frequencies: `{c: 1, a: 2, b: 3}`
   - `word2` frequencies: `{a: 1, b: 2, c: 3}`
   - Sorted frequencies for `word1`: `[1, 2, 3]`
   - Sorted frequencies for `word2`: `[1, 2, 3]`
   - Same distribution ✓

Since all conditions are met, we know we can transform `word1` to `word2`:
- Use Operation 2 to map: `c → a`, `a → b`, `b → c`
- Use Operation 1 to rearrange to desired order

### Edge Cases

- **Single character**: `word1 = "a"`, `word2 = "aa"` → Different lengths, returns `false`
- **Different character sets**: `word1 = "abc"`, `word2 = "abd"` → Different sets, returns `false`
- **Same characters, different frequencies**: `word1 = "aab"`, `word2 = "abb"` → Different frequency distributions, returns `false`
- **Identical strings**: Always returns `true` (trivially)

# Tags

#String #HashTable #Sorting #Frequency

