## Problem

https://leetcode.com/problems/generate-tag-for-video-caption/description/

```
You are given a string caption representing the caption for a video.

The following actions must be performed in order to generate a valid tag for the video:

1. Combine all words in the string into a single camelCase string prefixed with '#'. A camelCase string is one where the first letter of all words except the first one is capitalized. All characters after the first character in each word must be lowercase.

2. Remove all characters that are not an English letter, except the first '#'.

3. Truncate the result to a maximum of 100 characters.

Return the tag after performing the actions on caption.

Example 1:
Input: caption = "Leetcode daily streak achieved"
Output: "#leetcodeDailyStreakAchieved"
Explanation: The first letter for all words except "leetcode" should be capitalized.

Example 2:
Input: caption = "can I Go There"
Output: "#canIGoThere"
Explanation: The first letter for all words except "can" should be capitalized.

Example 3:
Input: caption = "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"
Output: "#hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"
Explanation: Since the first word has length 101, we need to truncate the last two letters from the word.

Constraints:
- 1 <= caption.length <= 150
- caption consists only of English letters and ' '.
```

## Observations

- The problem requires three distinct transformations: formatting to camelCase, cleaning non-alphabetic characters, and truncating to 100 characters
- The first word should be entirely lowercase, while subsequent words should be capitalized (first letter uppercase, rest lowercase)
- We need to handle the '#' prefix specially - it should be preserved even though it's not a letter
- The truncation happens **after** all transformations, not before
- Edge case: A single very long word (Example 3) shows that the 100-character limit includes the '#' prefix
- Multiple spaces between words are naturally handled by `split()` which filters empty strings

## Solution

### Approach: Three-Step Transformation

The solution follows the problem's requirements step-by-step:

**Step 1: Split and Format to camelCase**
- Split the caption into words using `split()` (handles multiple spaces automatically)
- Convert the first word to lowercase entirely
- For all subsequent words, convert to lowercase then capitalize the first letter
- This ensures proper camelCase formatting

**Step 2: Join and Clean**
- Join all words together with '#' prefix
- Iterate through characters (skipping the first '#')
- Keep only alphabetic characters
- This removes any non-letter characters while preserving the '#'

**Step 3: Truncate**
- Return only the first 100 characters of the result
- This ensures the tag doesn't exceed the maximum length

### Complexity Analysis

- **Time Complexity:** O(n) where n is the length of the caption
  - Splitting: O(n)
  - Processing words: O(n) 
  - Cleaning characters: O(n)
  - Truncation: O(1)
  
- **Space Complexity:** O(n) for storing the words list and cleaned character list

### Alternative One-Pass Approach

```python
class Solution:
    def generateTag(self, caption: str) -> str:
        words = caption.split()
        result = ['#']
        
        for i, word in enumerate(words):
            for j, ch in enumerate(word):
                if ch.isalpha():
                    if i == 0:
                        result.append(ch.lower())
                    elif j == 0:
                        result.append(ch.upper())
                    else:
                        result.append(ch.lower())
                        
                    if len(result) == 100:
                        return ''.join(result)
        
        return ''.join(result)
```

This alternative approach processes characters on-the-fly and can exit early once reaching 100 characters, but the original solution is clearer and more maintainable.

# Tags

#String #StringManipulation #Simulation

