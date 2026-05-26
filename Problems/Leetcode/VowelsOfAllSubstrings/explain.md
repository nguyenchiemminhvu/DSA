## Problem

https://leetcode.com/problems/vowels-of-all-substrings/

## Problem

https://leetcode.com/problems/vowels-of-all-substrings/

Given a string `word`, return the **sum of the number of vowels** ('a', 'e', 'i', 'o', and 'u') in **every substring** of `word`.

A substring is a contiguous (non-empty) sequence of characters within a string.

**Note:** Due to the large constraints, the answer may not fit in a signed 32-bit integer. Please be careful during the calculations.

### Examples

**Example 1:**
- Input: `word = "aba"`
- Output: `6`
- Explanation: 
  - All possible substrings are: "a", "ab", "aba", "b", "ba", and "a".
  - "b" has 0 vowels
  - "a", "ab", "ba", and "a" have 1 vowel each
  - "aba" has 2 vowels
  - Total: 0 + 1 + 1 + 1 + 1 + 2 = 6

**Example 2:**
- Input: `word = "abc"`
- Output: `3`
- Explanation:
  - All possible substrings are: "a", "ab", "abc", "b", "bc", and "c".
  - "a", "ab", and "abc" have 1 vowel each
  - "b", "bc", and "c" have 0 vowels
  - Total: 1 + 1 + 1 + 0 + 0 + 0 = 3

**Example 3:**
- Input: `word = "ltcd"`
- Output: `0`
- Explanation: There are no vowels in any substring.

### Constraints

- 1 <= word.length <= 10^5
- word consists of lowercase English letters

---

## Observations

### Key Insight: Contribution of Each Vowel

The naive approach would be to generate all substrings and count vowels in each, but that would be O(n²) or O(n³) in time complexity.

The **optimal approach** is to think about the **contribution of each character**:
- Instead of counting vowels in every substring, count **how many substrings contain each vowel**.

For a vowel at position `i` (0-indexed):
- **How many substrings start at or before this vowel?** 
  - Any substring can start at positions 0, 1, 2, ..., i (total: `i + 1` positions)
- **How many substrings end at or after this vowel?**
  - Any substring can end at positions i, i+1, i+2, ..., n-1 (total: `n - i` positions)
- **Total substrings containing the vowel at position i:** `(i + 1) * (n - i)`

This is the key observation that makes the problem solvable in **O(n)** time.

### Visual Example for "aba" (indices 0, 1, 2)

Position 0 is 'a' (vowel):
- Substrings starting at or before 0: just starting at 0 → 1 way
- Substrings ending at or after 0: can end at 0, 1, or 2 → 3 ways
- Contribution: 1 × 3 = 3 (appears in "a", "ab", "aba")

Position 1 is 'b' (not vowel):
- Skip this position

Position 2 is 'a' (vowel):
- Substrings starting at or before 2: can start at 0, 1, or 2 → 3 ways
- Substrings ending at or after 2: just ending at 2 → 1 way
- Contribution: 3 × 1 = 3 (appears in "ba", "aba", "a")

Total: 3 + 3 = 6 ✓

---

## Solution

### Algorithm: Contribution Counting

```python
class Solution:
    def countVowels(self, s: str) -> int:
        n = len(s)
        
        def vowel(x):
            return x == 'a' or x == 'e' or x == 'i' or x == 'o' or x == 'u'

        res = 0
        for i, c in enumerate(s):
            if vowel(c):
                # Each vowel at position i contributes (i+1) * (n-i) to the total
                res += (i + 1) * (n - i)
        return res
```

### Step-by-Step Breakdown

1. **Initialize:** Get string length `n` and result counter `res = 0`
2. **Define vowel check:** Create a helper function to identify vowels
3. **Iterate through string:** For each character at position `i`:
   - If it's a vowel:
     - Calculate its contribution: `(i + 1) * (n - i)`
    - Add contribution to result
4. **Return:** The total sum of vowel contributions

### Complexity Analysis

- **Time Complexity:** O(n)
  - Single pass through the string
  - Vowel check is O(1)
  
- **Space Complexity:** O(1)
  - Only using a few variables

### Why This Works

The formula `(i + 1) * (n - i)` counts exactly how many substrings contain the vowel at position `i`:
- **(i + 1):** Number of possible start positions (0 to i)
- **(n - i):** Number of possible end positions (i to n-1)
- **Product:** All combinations of start and end positions that include position i

By summing this for all vowels, we get the total count without explicitly generating substrings.

### Example Walkthrough: "aba"

- n = 3
- i=0, c='a' (vowel): contribution = (0+1) × (3-0) = 1 × 3 = 3
- i=1, c='b' (not vowel): skip
- i=2, c='a' (vowel): contribution = (2+1) × (3-2) = 3 × 1 = 3
- Result: 3 + 3 = **6** ✓

---

## Tags

- String
- Dynamic Programming / Mathematical Approach
- Contribution Counting
- Optimization
- Math Pattern Recognition

## Observations

## Solution

# Tags

