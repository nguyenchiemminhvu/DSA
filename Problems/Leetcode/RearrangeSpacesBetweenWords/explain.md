## Problem

https://leetcode.com/problems/rearrange-spaces-between-words/

```
You are given a string text of words that are placed among some number of spaces. Each word consists of one or more lowercase English letters and are separated by at least one space. It's guaranteed that text contains at least one word.

Rearrange the spaces so that there is an equal number of spaces between every pair of adjacent words and that number is maximized. If you cannot redistribute all the spaces equally, place the extra spaces at the end, meaning the returned string should be the same length as text.

Return the string after rearranging the spaces.

Example 1:
Input: text = "  this   is  a sentence "
Output: "this   is   a   sentence"
Explanation: There are a total of 9 spaces and 4 words. We can evenly divide the 9 spaces between the words: 9 / (4-1) = 3 spaces.

Example 2:
Input: text = " practice   makes   perfect"
Output: "practice   makes   perfect "
Explanation: There are a total of 7 spaces and 3 words. 7 / (3-1) = 3 spaces plus 1 extra space. We place this extra space at the end of the string.

Constraints:
- 1 <= text.length <= 100
- text consists of lowercase English letters and ' '.
- text contains at least one word.
```

## Observations

1. **Count spaces and words**: We need to count the total number of spaces in the input and extract all words.

2. **Edge case - Single word**: If there's only one word, all spaces should go at the end since there are no gaps between words.

3. **Distribution calculation**: 
   - For `n` words, there are `n-1` gaps between them
   - Spaces per gap = `total_spaces // (n-1)`
   - Extra spaces = `total_spaces % (n-1)` (these go at the end)

4. **String manipulation**: Python's `split()` without arguments automatically handles multiple consecutive spaces and extracts all words.

5. **Result construction**: Use `join()` to efficiently concatenate words with the calculated spaces between them.

## Solution

**Complexity Analysis:**
- **Time Complexity**: O(n) where n is the length of the text
  - `split()`: O(n) to scan through the text
  - `count()`: O(n) to count spaces
  - `join()`: O(n) to construct the result
- **Space Complexity**: O(n) for storing the words array and result string

**How it works:**

1. **Example 1**: `text = "  this   is  a sentence "`
   - Words: `["this", "is", "a", "sentence"]` (n=4)
   - Total spaces: 9
   - Spaces per gap: 9 // (4-1) = 3
   - Extra spaces: 9 % (4-1) = 0
   - Result: `"this   is   a   sentence"`

2. **Example 2**: `text = " practice   makes   perfect"`
   - Words: `["practice", "makes", "perfect"]` (n=3)
   - Total spaces: 7
   - Spaces per gap: 7 // (3-1) = 3
   - Extra spaces: 7 % (3-1) = 1
   - Result: `"practice   makes   perfect "`

**Key Insights:**
- The solution elegantly uses Python's `join()` method to insert the same number of spaces between all words
- The modulo operation naturally handles the "extra" spaces that can't be evenly distributed
- The single-word edge case is handled separately to avoid division by zero

# Tags
String, Simulation, Array

