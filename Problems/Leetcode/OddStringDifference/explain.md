## Problem

https://leetcode.com/problems/odd-string-difference/description/

```
You are given an array of equal-length strings words. Assume that the length of each string is n.

Each string words[i] can be converted into a difference integer array difference[i] of length n - 1 where difference[i][j] = words[i][j+1] - words[i][j] where 0 <= j <= n - 2. Note that the difference between two letters is the difference between their positions in the alphabet i.e. the position of 'a' is 0, 'b' is 1, and 'z' is 25.

For example, for the string "acb", the difference integer array is [2 - 0, 1 - 2] = [2, -1].
All the strings in words have the same difference integer array, except one. You should find that string.

Return the string in words that has different difference integer array.

Example 1:

Input: words = ["adc","wzy","abc"]
Output: "abc"
Explanation: 
- The difference integer array of "adc" is [3 - 0, 2 - 3] = [3, -1].
- The difference integer array of "wzy" is [25 - 22, 24 - 25]= [3, -1].
- The difference integer array of "abc" is [1 - 0, 2 - 1] = [1, 1]. 
The odd array out is [1, 1], so we return the corresponding string, "abc".

Example 2:

Input: words = ["aaa","bob","ccc","ddd"]
Output: "bob"
Explanation: All the integer arrays are [0, 0] except for "bob", which corresponds to [13, -13].

Constraints:

3 <= words.length <= 100
n == words[i].length
2 <= n <= 20
words[i] consists of lowercase English letters.
```

## Observations

1. **Difference Array Calculation**: Each word is converted to a "difference array" where each element represents the difference between consecutive characters' ASCII values.

2. **Pattern Recognition**: All words except one will have the same difference array pattern. We need to find the unique one.

3. **Counting Strategy**: We can use a frequency map to count how many words produce each difference pattern.

4. **Unique Identifier**: The word with a difference pattern that appears only once is our answer.

5. **ASCII Arithmetic**: `ord(char)` gives the ASCII value, so `ord(word[j]) - ord(word[j-1])` calculates the difference between consecutive characters.

## Solution

1. **Initialize Dictionary**: `f = {}` stores difference patterns as keys and `[index, count]` as values.

2. **Process Each Word**: 
   - For each word, calculate its difference array by finding `ord(word[j]) - ord(word[j-1])` for consecutive characters
   - Convert to tuple `tdiff` (tuples are hashable and can be dictionary keys)

3. **Track Patterns**: 
   - `f[tdiff][0]` stores the index of a word with this pattern
   - `f[tdiff][1]` counts how many words have this pattern

4. **Find the Odd One Out**: 
   - Iterate through the frequency map
   - Return the word at index `v[0]` for the pattern that appears only once (`v[1] == 1`)

**Time Complexity**: O(n × m) where n is the number of words and m is the length of each word
**Space Complexity**: O(n × m) for storing difference arrays

**Example Walkthrough** with `["adc", "wzy", "abc"]`:
- "adc": diff = [3-0, 2-3] = [3, -1]
- "wzy": diff = [25-22, 24-25] = [3, -1] 
- "abc": diff = [1-0, 2-1] = [1, 1]

Pattern [3, -1] appears twice, [1, 1] appears once → return "abc"

# Tags

`Array` `Hash Table` `String`

