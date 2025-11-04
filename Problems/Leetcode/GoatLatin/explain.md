## Problem

https://leetcode.com/problems/goat-latin/description/

```
You are given a string sentence that consist of words separated by spaces. Each word consists of lowercase and uppercase letters only.

We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.) The rules of Goat Latin are as follows:

If a word begins with a vowel ('a', 'e', 'i', 'o', or 'u'), append "ma" to the end of the word.
For example, the word "apple" becomes "applema".
If a word begins with a consonant (i.e., not a vowel), remove the first letter and append it to the end, then add "ma".
For example, the word "goat" becomes "oatgma".
Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
For example, the first word gets "a" added to the end, the second word gets "aa" added to the end, and so on.
Return the final sentence representing the conversion from sentence to Goat Latin.

Example 1:

Input: sentence = "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"

Example 2:

Input: sentence = "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"

Constraints:

1 <= sentence.length <= 150
sentence consists of English letters and spaces.
sentence has no leading or trailing spaces.
All the words in sentence are separated by a single space.
```

## Observations

1. **Two main transformation rules based on first character:**
   - If word starts with vowel (a, e, i, o, u): append "ma"
   - If word starts with consonant: move first letter to end, then append "ma"

2. **Position-based suffix:** Each word gets additional 'a's equal to its position (1-indexed)
   - 1st word: +1 'a'
   - 2nd word: +2 'a's  
   - 3rd word: +3 'a's, etc.

3. **Case sensitivity:** Vowels can be uppercase or lowercase (aeiouAEIOU)

4. **String manipulation steps:**
   - Split sentence into words
   - Transform each word according to rules
   - Join words back with spaces

## Solution

**Algorithm:**
1. Split the input sentence into individual words
2. For each word at index `i`:
   - Check if first character is vowel (case-insensitive)
   - If vowel: word + "ma" + (i+1) 'a's
   - If consonant: word[1:] + word[0] + "ma" + (i+1) 'a's
3. Join all transformed words with spaces

**Time Complexity:** O(n*m) where n is number of words and m is average word length
**Space Complexity:** O(n*m) for storing the result

**Key Implementation Details:**
- `s.split()` handles word separation
- `l[i][0] in "aeiouAEIOU"` checks for vowels (both cases)
- `l[i][1:] + l[i][0]` moves first character to end
- `'a' * (i + 1)` generates position-based suffix
- `" ".join(l)` reconstructs the sentence

**Example walkthrough with "I speak":**
- "I" (vowel): "I" + "ma" + "a" = "Ima" + "a" = "Imaa"
- "speak" (consonant): "peak" + "s" + "ma" + "aa" = "peaksmaaa"
- Result: "Imaa peaksmaaa"

# Tags

String Manipulation, Array Processing, Implementation

