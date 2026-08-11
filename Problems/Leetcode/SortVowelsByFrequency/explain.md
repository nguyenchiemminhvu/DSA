## Problem

https://leetcode.com/problems/sort-vowels-by-frequency/description/

```
You are given a string s consisting of lowercase English characters.

Rearrange only the vowels in the string so that they appear in non-increasing order of their frequency.

If multiple vowels have the same frequency, order them by the position of their first occurrence in s.

Return the modified string.

Vowels are 'a', 'e', 'i', 'o', and 'u'.

The frequency of a letter is the number of times it occurs in the string.

Example 1:

Input: s = "leetcode"
Output: "leetcedo"
Explanation:
Vowels in the string are ['e', 'e', 'o', 'e'] with frequencies: e = 3, o = 1.
Sorting in non-increasing order of frequency and placing them back into the vowel positions results in "leetcedo".

Example 2:

Input: s = "aeiaaioooa"
Output: "aaaaoooiie"
Explanation:
Vowels in the string are ['a', 'e', 'i', 'a', 'a', 'i', 'o', 'o', 'o', 'a'] with frequencies: a = 4, o = 3, i = 2, e = 1.
Sorting them in non-increasing order of frequency and placing them back into the vowel positions results in "aaaaoooiie".

Example 3:

Input: s = "baeiou"
Output: "baeiou"
Explanation:
Each vowel appears exactly once, so all have the same frequency.
Thus, they retain their relative order based on first occurrence, and the string remains unchanged.

Constraints:

1 <= s.length <= 10^5
s consists of lowercase English letters.
```

## Observations

1. **Separate vowels from consonants**: The consonants are never moved — only vowel positions need to be filled with rearranged vowels.

2. **Frequency counting**: Count how many times each vowel appears in `s` using a hash map.

3. **Tie-breaking by first occurrence**: When two vowels share the same frequency, the one that appears first in `s` should come first in the sorted order. This means we need to record the first occurrence index of each vowel.

4. **Sorting key**: Sort the distinct vowels by `(-frequency, first_occurrence_index)` — descending frequency first, then ascending first-occurrence position as a tiebreaker.

5. **Reconstruct sorted vowel sequence**: After sorting, expand each vowel into `frequency` copies to get the full ordered vowel sequence.

6. **Rebuild the string**: Walk through the original string. For each vowel position, replace it with the next character from the sorted vowel sequence; leave consonant positions unchanged.

## Solution

The algorithm uses a **frequency map + custom sort + two-pointer fill**:

### Algorithm Steps:

1. **Count frequencies and first occurrences**: Iterate through `s` once, tracking `freq[v]` and `first[v]` for each vowel `v`.

2. **Sort distinct vowels**: Sort the set of vowels found in `s` by the key `(-freq[v], first[v])`.

3. **Expand sorted vowels**: Build a list `sorted_vowels` by repeating each sorted vowel `freq[v]` times.

4. **Rebuild the result**: Iterate through the original string with a pointer `j` into `sorted_vowels`. For each character:
   - If it is a vowel, write `sorted_vowels[j]` and advance `j`.
   - Otherwise, keep the original consonant.

### Example Walkthrough:

For `s = "leetcode"`:
- Vowels found: `e` (freq=3, first=1), `o` (freq=1, first=5)
- Sort key: `e → (-3, 1)`, `o → (-1, 5)` → order: `[e, o]`
- Expanded: `['e','e','e','o']`
- Vowel positions in `s`: indices 1, 2, 5, 7 → filled with `e, e, e, o`
- Result: `"leetcedo"` ✓

For `s = "baeiou"`:
- All vowels appear once: `a(1,1)`, `e(1,2)`, `i(1,3)`, `o(1,4)`, `u(1,5)`
- Sort key ties on freq=1, broken by first occurrence → order unchanged: `[a,e,i,o,u]`
- Result: `"baeiou"` ✓

### Complexity:
- **Time**: O(n + V log V) where n = len(s), V ≤ 5 (number of distinct vowels) → effectively O(n)
- **Space**: O(n) for the sorted vowel list and result

## Tags

string, hash map, sorting, greedy
