## Problem

https://leetcode.com/problems/smallest-palindromic-rearrangement-i/

You are given a **palindromic** string `s`.

Return the **lexicographically smallest** palindromic permutation of `s`.

**Constraints:**
- `1 <= s.length <= 10^5`
- `s` consists of lowercase English letters.
- `s` is guaranteed to be palindromic.

**Examples:**
1. Input: `s = "z"` → Output: `"z"`
   - A single character is already the smallest palindrome.
2. Input: `s = "babab"` → Output: `"abbba"`
   - Rearranging `"babab"` → `"abbba"` gives the smallest lexicographic palindrome.
3. Input: `s = "daccad"` → Output: `"acddca"`
   - Rearranging `"daccad"` → `"acddca"` gives the smallest lexicographic palindrome.

## Observations

1. **Input is guaranteed palindromic**: This means every character appears an even number of times, except possibly one character that appears an odd number of times (which would sit in the middle).

2. **Palindrome structure**: A palindrome is fully determined by its first half (and optionally a middle character). The second half is the mirror of the first. So we only need to decide the **first half** optimally.

3. **Lexicographically smallest palindrome**: To minimise the palindrome lexicographically, we should arrange the first half in ascending (sorted) order. The second half is the reverse of the first half.

4. **Counting characters**: Count the frequency of each character. For each character, the number of pairs is `freq[c] // 2`. Place `freq[c] // 2` copies of `c` in the first half, sorted in ascending order. If any character has an odd frequency, it goes in the middle.

5. **Algorithm summary**:
   - Count frequencies.
   - Build the sorted first half from pairs of each character (in alphabetical order).
   - If there is a character with odd frequency, place one copy of it in the middle.
   - Construct result = `first_half + middle + reverse(first_half)`.

## Solution

**Algorithm: Frequency Count + Greedy Sorting**

```python
class Solution:
    def smallestPalindrome(self, s: str) -> str:
        from collections import Counter

        freq = Counter(s)
        first_half = []
        middle = ""

        for c in sorted(freq.keys()):
            pairs = freq[c] // 2
            first_half.append(c * pairs)
            if freq[c] % 2 == 1:
                middle = c  # at most one odd-frequency character (guaranteed by input)

        half = "".join(first_half)
        return half + middle + half[::-1]
```

**Key Steps:**

1. **Count frequencies** of all characters using a hash map.
2. **Iterate characters in sorted order**: for each character, take `freq[c] // 2` pairs and append them to the first half.
3. **Detect the middle character**: if any character has an odd frequency, record it (there can be at most one, since the input is palindromic).
4. **Construct the result**: `first_half + middle_char + reversed(first_half)`.

**Time Complexity**: O(n) — counting frequencies is O(n); building the half string is O(n); reversing is O(n). Sorting over the alphabet is O(26 log 26) = O(1).

**Space Complexity**: O(n) — for the output string and the frequency map.

# Tags

`String`, `Greedy`, `Sorting`, `Frequency Count`, `Palindrome`

