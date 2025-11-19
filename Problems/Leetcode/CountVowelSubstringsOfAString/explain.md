## Problem

https://leetcode.com/problems/count-vowel-substrings-of-a-string/

```
A substring is a contiguous (non-empty) sequence of characters within a string.

A vowel substring is a substring that only consists of vowels ('a', 'e', 'i', 'o', and 'u') and has all five vowels present in it.

Given a string word, return the number of vowel substrings in word.

Example 1:

Input: word = "aeiouu"
Output: 2
Explanation: The vowel substrings of word are as follows (underlined):
- "aeiouu"
- "aeiouu"

Example 2:

Input: word = "unicornarihan"
Output: 0
Explanation: Not all 5 vowels are present, so there are no vowel substrings.

Example 3:

Input: word = "cuaieuouac"
Output: 7
Explanation: The vowel substrings of word are as follows (underlined):
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"
- "cuaieuouac"

Constraints:

1 <= word.length <= 100
word consists of lowercase English letters only.
```

## Observations

Looking at the problem requirements:
1. We need to find substrings that contain ONLY vowels ('a', 'e', 'i', 'o', 'u')
2. The substring must contain ALL five vowels at least once
3. We need to count all such valid substrings

Key insights:
- Any character that is not a vowel breaks the continuity, so we can reset our search
- Once we have a valid window containing all 5 vowels, we can extend it to the right as long as we encounter vowels
- We need to use a sliding window approach with frequency counting
- When we have all 5 vowels in our current window, we can count all possible extensions to the right

## Solution

1. **Sliding Window Setup**: Use two pointers `l` and `r` to maintain a window, with a frequency map `f` to track vowel counts.

2. **Reset on Non-Vowel**: When encountering a non-vowel character, reset the frequency map and move both pointers to the next position since non-vowels break vowel-only substrings.

3. **Expand Window**: When encountering a vowel, add it to the frequency map and expand the right pointer.

4. **Count Valid Substrings**: When the current window contains all 5 vowels:
   - From the current position `r`, extend as far right as possible while staying within vowels
   - Each extension creates a valid substring starting from `l`
   - Count all these extensions

5. **Shrink Window**: Remove the leftmost character from the window and continue to find other valid windows.

**Time Complexity**: O(n²) in worst case, where n is the length of the string. The inner while loop that extends to the right can iterate up to n times for each position.

**Space Complexity**: O(1) since we only store at most 5 vowels in the frequency map.

**Example Walkthrough** (word = "aeiouu"):
- When l=0, r=4: window "aeiou" contains all vowels
  - Can extend to include "u" at index 5: substring "aeiouu" ✓
  - Total: 1 substring
- When l=1, r=5: window "eiouu" contains all vowels  
  - Cannot extend further
  - Total: 1 more substring
- Final result: 2 substrings

# Tags

- Sliding Window
- Two Pointers  
- Hash Map/Frequency Counting
- String Processing

