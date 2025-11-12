## Problem

https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/description/

```
You are given an array of strings words (0-indexed).

In one operation, pick two distinct indices i and j, where words[i] is a non-empty string, and move any character from words[i] to any position in words[j].

Return true if you can make every string in words equal using any number of operations, and false otherwise.

Example 1:

Input: words = ["abc","aabc","bc"]
Output: true
Explanation: Move the first 'a' in words[1] to the front of words[2],
to make words[1] = "abc" and words[2] = "abc".
All the strings are now equal to "abc", so return true.

Example 2:

Input: words = ["ab","a"]
Output: false
Explanation: It is impossible to make all the strings equal using the operation.

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of lowercase English letters.
```

## Observations

1. **Key Insight**: For all strings to be equal after redistribution, each character must appear the same number of times in the final equal strings.

2. **Mathematical Requirement**: If we have `n` strings and want them all to be equal, then the total count of each character across all strings must be divisible by `n`.

3. **Redistribution Freedom**: We can move any character from any string to any position in any other string, giving us complete freedom to redistribute characters.

4. **Single String Edge Case**: If there's only one string, it's already "equal" to itself.

5. **Character Frequency Analysis**: We need to count the total frequency of each character across all strings and check if each frequency is divisible by the number of strings.

## Solution

The solution uses a **frequency counting approach**:

1. **Edge Case Handling**: If there's only one string, return `True` immediately since it's trivially equal to itself.

2. **Character Frequency Counting**: 
   - Use a `Counter` to accumulate character frequencies across all strings
   - For each word, convert it to a list of characters and count them
   - Add these counts to the main frequency counter

3. **Divisibility Check**:
   - For each character's total frequency, check if it's divisible by `n` (number of strings)
   - If ALL character frequencies are divisible by `n`, return `True`
   - If ANY character frequency is not divisible by `n`, return `False`

**Why this works**:
- If a character appears `k` times total and we have `n` strings, each final string must contain exactly `k/n` occurrences of that character
- This is only possible if `k` is divisible by `n`
- Since we can redistribute characters freely, divisibility is both necessary and sufficient

**Time Complexity**: O(m) where m is the total number of characters across all strings
**Space Complexity**: O(1) since we only store at most 26 character counts (lowercase English letters)

**Example Walkthrough**:
- `words = ["abc","aabc","bc"]`
- Character frequencies: a=2, b=3, c=3
- n=3 strings
- Check: 2%3≠0, so return `False`... Wait, let me recalculate:
- Actually: a=2, b=3, c=3. For the example to return `True`, let me recheck...
- In "abc": a=1, b=1, c=1
- In "aabc": a=2, b=1, c=1  
- In "bc": b=1, c=1
- Total: a=3, b=3, c=3
- All divisible by 3, so return `True` ✓

# Tags

- Hash Table
- String
- Counting
- Mathematical

