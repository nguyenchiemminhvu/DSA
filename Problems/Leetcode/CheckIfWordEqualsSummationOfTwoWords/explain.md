## Problem

https://leetcode.com/problems/check-if-word-equals-summation-of-two-words/description/

```
The letter value of a letter is its position in the alphabet starting from 0 (i.e. 'a' -> 0, 'b' -> 1, 'c' -> 2, etc.).

The numerical value of some string of lowercase English letters s is the concatenation of the letter values of each letter in s, which is then converted into an integer.

For example, if s = "acb", we concatenate each letter's letter value, resulting in "021". After converting it, we get 21.
You are given three strings firstWord, secondWord, and targetWord, each consisting of lowercase English letters 'a' through 'j' inclusive.

Return true if the summation of the numerical values of firstWord and secondWord equals the numerical value of targetWord, or false otherwise.

Example 1:

Input: firstWord = "acb", secondWord = "cba", targetWord = "cdb"
Output: true
Explanation:
The numerical value of firstWord is "acb" -> "021" -> 21.
The numerical value of secondWord is "cba" -> "210" -> 210.
The numerical value of targetWord is "cdb" -> "231" -> 231.
We return true because 21 + 210 == 231.

Example 2:

Input: firstWord = "aaa", secondWord = "a", targetWord = "aab"
Output: false
Explanation: 
The numerical value of firstWord is "aaa" -> "000" -> 0.
The numerical value of secondWord is "a" -> "0" -> 0.
The numerical value of targetWord is "aab" -> "001" -> 1.
We return false because 0 + 0 != 1.

Example 3:

Input: firstWord = "aaa", secondWord = "a", targetWord = "aaaa"
Output: true
Explanation: 
The numerical value of firstWord is "aaa" -> "000" -> 0.
The numerical value of secondWord is "a" -> "0" -> 0.
The numerical value of targetWord is "aaaa" -> "0000" -> 0.
We return true because 0 + 0 == 0.

Constraints:

1 <= firstWord.length, secondWord.length, targetWord.length <= 8
firstWord, secondWord, and targetWord consist of lowercase English letters from 'a' to 'j' inclusive.
```

## Observations

1. **Letter-to-Number Mapping**: Each letter from 'a' to 'j' maps to its 0-based position ('a'=0, 'b'=1, 'c'=2, ..., 'j'=9).

2. **String-to-Number Conversion**: For any string, we concatenate the numeric values of each letter to form a number string, then convert it to integer.
   - Example: "acb" → "a"=0, "c"=2, "b"=1 → "021" → 21

3. **Summation Check**: We need to verify if `numerical_value(firstWord) + numerical_value(secondWord) == numerical_value(targetWord)`

4. **Key Insights**:
   - Only letters 'a' through 'j' are used (0-9 mapping)
   - Leading zeros in the concatenated string are automatically handled when converting to integer
   - The conversion process is identical for all three words

5. **Edge Cases**:
   - Words with all 'a' characters result in numbers with leading zeros (e.g., "aaa" → "000" → 0)
   - Single character words work the same way
   - The constraint ensures only 10 letters ('a' to 'j'), making each letter map to a single digit

## Solution

The solution uses a **direct string-to-number conversion** approach:

### Algorithm Steps:

1. **Letter Value Conversion**: For each word, convert every character to its numeric value using `ord(c) - ord('a')`
   - This gives us 'a'=0, 'b'=1, 'c'=2, ..., 'j'=9

2. **String Concatenation**: Join all numeric values into a single string for each word
   - Use `"".join(str(ord(c) - ord('a')) for c in word)`

3. **Integer Conversion**: Convert each concatenated string to integer
   - `int(concatenated_string)` automatically handles leading zeros

4. **Summation Check**: Return whether `int(sa) + int(sb) == int(sc)`

### Example Walkthrough:
For `firstWord = "acb"`, `secondWord = "cba"`, `targetWord = "cdb"`:
- `sa = "021"` → `int(sa) = 21`
- `sb = "210"` → `int(sb) = 210` 
- `sc = "231"` → `int(sc) = 231`
- Result: `21 + 210 == 231` → `True`

### Time Complexity: O(n)
- O(n) to process each word where n is the total length of all words
- String concatenation and integer conversion are linear operations

### Space Complexity: O(n)
- O(n) space for storing the concatenated numeric strings

**Key Insight**: The solution elegantly handles the letter-to-digit conversion by leveraging ASCII values and Python's string operations, making the numeric conversion straightforward and efficient.

# Tags

