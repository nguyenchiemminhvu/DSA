## Problem

https://leetcode.com/problems/merge-strings-alternately/description/

```
You are given two strings word1 and word2. Merge the strings by adding letters in alternating order, starting with word1. If a string is longer than the other, append the additional letters onto the end of the merged string.

Return the merged string.

Example 1:

Input: word1 = "abc", word2 = "pqr"
Output: "apbqcr"
Explanation: The merged string will be merged as so:
word1:  a   b   c
word2:    p   q   r
merged: a p b q c r

Example 2:

Input: word1 = "ab", word2 = "pqrs"
Output: "apbqrs"
Explanation: Notice that as word2 is longer, "rs" is appended to the end.
word1:  a   b 
word2:    p   q   r   s
merged: a p b q   r   s

Example 3:

Input: word1 = "abcd", word2 = "pq"
Output: "apbqcd"
Explanation: Notice that as word1 is longer, "cd" is appended to the end.
word1:  a   b   c   d
word2:    p   q 
merged: a p b q c   d

Constraints:

1 <= word1.length, word2.length <= 100
word1 and word2 consist of lowercase English letters.
```

## Observations

1. **Problem Pattern**: This is a string merging problem where we need to interleave characters from two strings alternately.

2. **Key Requirements**:
   - Start with the first string (word1/a)
   - Alternate between characters from both strings
   - Handle remaining characters when strings have different lengths

3. **Edge Cases**:
   - One string is longer than the other
   - Strings of equal length
   - One string is empty (though constraints guarantee length >= 1)

4. **Approach Analysis**:
   - Use `zip()` to pair characters from both strings
   - Flatten the pairs to create alternating sequence
   - Append remaining characters from the longer string

## Solution

1. **Get lengths**: Store lengths of both strings for later use
   ```python
   na, nb = len(a), len(b)
   ```

2. **Create alternating sequence**: Use `zip()` and list comprehension
   ```python
   res = [c for p in zip(a, b) for c in p]
   ```
   - `zip(a, b)` pairs characters: `('a','p'), ('b','q'), ('c','r')`
   - The nested comprehension flattens pairs: `['a','p','b','q','c','r']`
   - This automatically handles the common length portion

3. **Handle remaining characters**: Append leftover characters from longer string
   ```python
   if na < nb:
       res.extend(b[na:])  # Append remaining from b
   else:
       res.extend(a[nb:])  # Append remaining from a
   ```

4. **Return result**: Join the character list into a string
   ```python
   return "".join(res)
   ```

**Time Complexity**: O(n + m) where n and m are lengths of the input strings
**Space Complexity**: O(n + m) for the result list

**Example Walkthrough** (word1="abc", word2="pqr"):
1. `zip("abc", "pqr")` → `[('a','p'), ('b','q'), ('c','r')]`
2. List comprehension → `['a','p','b','q','c','r']`
3. No remaining characters (equal lengths)
4. Join → `"apbqcr"`

# Tags

- String Manipulation
- Two Pointers
- Array/List Operations

