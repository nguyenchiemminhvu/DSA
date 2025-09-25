## Problem Description

https://leetcode.com/problems/sort-vowels-in-a-string/description/

```
Given a 0-indexed string s, permute s to get a new string t such that:

All consonants remain in their original places. More formally, if there is an index i with 0 <= i < s.length such that s[i] is a consonant, then t[i] = s[i].
The vowels must be sorted in the nondecreasing order of their ASCII values. More formally, for pairs of indices i, j with 0 <= i < j < s.length such that s[i] and s[j] are vowels, then t[i] must not have a higher ASCII value than t[j].
Return the resulting string.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in lowercase or uppercase. Consonants comprise all letters that are not vowels.

Example 1:

Input: s = "lEetcOde"
Output: "lEOtcede"
Explanation: 'E', 'O', and 'e' are the vowels in s; 'l', 't', 'c', and 'd' are all consonants. The vowels are sorted according to their ASCII values, and the consonants remain in the same places.

Example 2:

Input: s = "lYmpH"
Output: "lYmpH"
Explanation: There are no vowels in s (all characters in s are consonants), so we return "lYmpH".

Constraints:

1 <= s.length <= 105
s consists only of letters of the English alphabet in uppercase and lowercase.
```

## Observations

**First idea (simple, intuitive):**

- Traverse the string once.
- If a character is a vowel, append it to a temporary string/list.
- Sort that temporary list of vowels.
- Traverse the original string again:
- When you meet a vowel, replace it with the next character from the sorted temporary list.
- Move to the next character in the sorted list.

**Pros**: Simple and easy to understand.

**Cons**: Requires scanning the string twice and doing an explicit sort of the collected vowels.

**Second idea (frequency-count approach)**

- Create a fixed list of vowels ordered by ASCII: ```A E I O U a e i o u```
- Maintain a frequency counter for those vowel characters (you used an ASCII-indexed array).
- Scan the input string once and increment the count for each vowel.
- Scan the string again
  - whenever a vowel is encountered, pick the earliest vowel (in ASCII order) that still has count > 0, place it there
  - and decrement its count.

**Pros**: Fewer work for sorting (you avoid an explicit sort) and only small fixed extra memory for the frequency buffer. Performance is optimal (linear).

**Cons:** Needs a small fixed buffer to hold frequencies (constant extra space).

## Complexity

**Time**: O(n + V) where n is len(s) and V is a small constant (the vowel list / ASCII scan). Practically O(n).

**Space**: O(1) extra (fixed counter array and small constants).

## Tags

array, string, sorting