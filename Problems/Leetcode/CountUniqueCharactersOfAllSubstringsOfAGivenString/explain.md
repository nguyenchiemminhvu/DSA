## Problem

https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/description

Given a string `s`, return the sum of `countUniqueChars(t)` for all substrings `t` of `s`, where `countUniqueChars(t)` returns the number of characters in `t` that appear exactly once in `t`.

**Example 1:**
- Input: `s = "ABC"`
- Output: `10`
- Explanation: All possible substrings are: `"A"`, `"B"`, `"C"`, `"AB"`, `"BC"`, `"ABC"`. Every substring is composed with only unique letters. Sum: $1 + 1 + 1 + 2 + 2 + 3 = 10$

**Example 2:**
- Input: `s = "ABA"`
- Output: `8`
- Explanation: Substrings: `"A"` (1), `"B"` (1), `"A"` (1), `"AB"` (2), `"BA"` (2), `"ABA"` (1). Sum: $1 + 1 + 1 + 2 + 2 + 1 = 8$

**Example 3:**
- Input: `s = "LEETCODE"`
- Output: `92`

**Constraints:**
- $1 \leq \text{len}(s) \leq 10^5$
- $s$ consists of uppercase English letters only
- Answer fits in a 32-bit integer

## Observations

### Key Insights

1. **Brute Force Approach**: We could enumerate all substrings and count unique characters in each, but this is $O(n^3)$ which is too slow.

2. **Contribution-Based Thinking**: Instead of iterating through all substrings, think about the **contribution** of each character to the final answer.
   - For each character `c` at position `i`, we need to count how many substrings have `c` appearing exactly once.

3. **Counting Substrings with Unique Character**: For a character `c` at position `i`:
   - A substring contains `c` as a unique character if:
     - The substring includes position `i`
     - There's no other `c` in the substring
   
4. **Boundaries Matter**: If `c` appears at positions `...prev_left, prev_right, i, next_left, next_right...`, then for the occurrence at position `i`:
   - The substring must start **after** the previous occurrence (at positions `prev_right + 1` to `i`)
   - The substring must end **before** the next occurrence (at positions `i` to `next_left - 1`)
   - Number of valid substrings = $(i - \text{prev_right}) \times (\text{next_left} - i)$

5. **Preprocessing**: Store all positions of each character in a map, then for each character, calculate the contribution of each occurrence.

### Algorithm Summary
- Group indices by character
- For each character `c` with positions in array `arr`:
  - Add sentinel values: `-1` at start and `n` at end to handle boundaries
  - For each occurrence at index `i`, calculate contribution as: $(arr[i] - arr[i-1]) \times (arr[i+1] - arr[i])$
- Sum all contributions

## Solution

```python
from collections import defaultdict
import string

class Solution:
    def uniqueLetterString(self, s: str) -> int:
        n = len(s)
        mp = defaultdict(list)
        
        # Store indices of each character
        for i, c in enumerate(s):
            mp[c].append(i)
        
        res = 0
        
        # For each uppercase letter
        for c in string.ascii_uppercase:
            arr = [-1] + mp[c] + [n]
            
            # For each occurrence of character c
            for i in range(1, len(arr) - 1):
                # Contribution of c at position arr[i]
                # = (ways to choose left boundary) * (ways to choose right boundary)
                res += (arr[i] - arr[i - 1]) * (arr[i + 1] - arr[i])
        
        return res
```

### Complexity Analysis
- **Time Complexity**: $O(n + 26 \times m)$ where $n$ is the string length and $m$ is the average number of occurrences per character. Since there are at most 26 unique letters and at most $n$ occurrences total, this simplifies to $O(n)$.
- **Space Complexity**: $O(n)$ for the map storing character indices.

### Step-by-Step Example: `s = "ABA"`

**Indices**: A→[0, 2], B→[1]

**For character A** with positions:
- arr = [-1, 0, 2, 3]
- At index 0: $(0 - (-1)) \times (2 - 0) = 1 \times 2 = 2$
- At index 2: $(2 - 0) \times (3 - 2) = 2 \times 1 = 2$
- Subtotal: 4

**For character B** with positions:
- arr = [-1, 1, 3]
- At index 1: $(1 - (-1)) \times (3 - 1) = 2 \times 2 = 4$
- Subtotal: 4

**Total**: $4 + 4 = 8$ ✓

## Tags

- Array
- String
- Dynamic Programming
- Contribution Counting
- Hash Map

