## Problem

https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/description/

```
You are given a string s formed by digits and '#'. We want to map s to English lowercase characters as follows:

Characters ('a' to 'i') are represented by ('1' to '9') respectively.
Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.
Return the string formed after mapping.

The test cases are generated so that a unique mapping will always exist.

Example 1:

Input: s = "10#11#12"
Output: "jkab"
Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".

Example 2:

Input: s = "1326#"
Output: "acz"

Constraints:

1 <= s.length <= 1000
s consists of digits and the '#' letter.
s will be a valid string such that mapping is always possible.
```

## Observations

1. **Mapping Rules**:
   - Characters 'a' to 'i' are mapped from '1' to '9' (single digits)
   - Characters 'j' to 'z' are mapped from '10#' to '26#' (two digits followed by '#')

2. **Key Insight**: The '#' character acts as a **delimiter** that tells us the preceding two digits should be treated as a single character mapping.

3. **Parsing Strategy**: 
   - When we encounter '#', we know the previous 2 digits form a single character (j-z)
   - When we encounter a digit (not preceded by '#'), it represents a single character (a-i)

4. **Direction Matters**: Since we need to distinguish between patterns like "12" vs "1" + "2#", it's easier to **parse from right to left**:
   - If we see '#', we know the 2 digits before it belong together
   - If we see a digit without '#' after it, it's a standalone mapping

5. **String Construction**: Since we parse right-to-left but need the result left-to-right, we'll need to reverse the final result.

## Solution

The solution uses a **reverse iteration approach** to correctly identify character boundaries:

### Algorithm Steps:

1. **Start from the End**: Initialize pointer `i` at the last character of string `s`

2. **Check Current Character**:
   - **If `s[i] == '#'`**: 
     - Extract two digits before '#': `s[i-2]` and `s[i-1]`
     - Convert to number: `int(s[i-2]) * 10 + int(s[i-1])`
     - Map to character: `chr(ord('a') + number - 1)`
     - Move pointer back by 3 positions (`i -= 3`)
   
   - **If `s[i]` is a digit**:
     - Convert single digit to character: `chr(ord('a') + int(s[i]) - 1)`
     - Move pointer back by 1 position (`i -= 1`)

3. **Build Result**: Append each decoded character to result string

4. **Reverse Result**: Since we built the string backwards, reverse it before returning

### Example Walkthrough:

**Input**: `s = "1326#"`

- `i = 4`: `s[4] = '#'` 
  - Extract: `s[2] = '2'`, `s[3] = '6'` → `26`
  - Character: `chr(ord('a') + 26 - 1) = chr(122) = 'z'`
  - `res = "z"`, `i = 1`

- `i = 1`: `s[1] = '3'` (digit)
  - Character: `chr(ord('a') + 3 - 1) = chr(99) = 'c'` 
  - `res = "zc"`, `i = 0`

- `i = 0`: `s[0] = '1'` (digit)
  - Character: `chr(ord('a') + 1 - 1) = chr(97) = 'a'`
  - `res = "zca"`, `i = -1`

- **Final**: `res[::-1] = "acz"`

### Time Complexity: O(n)
- We visit each character in the string exactly once
- String reversal takes O(n) time

### Space Complexity: O(n)
- We store the result string which can be at most n characters long

### Key Insights:
- **Right-to-left parsing** eliminates ambiguity in character boundary detection
- **Character arithmetic**: `chr(ord('a') + number - 1)` converts number to corresponding alphabet character
- **Greedy approach**: Always prioritize longer patterns ('#' patterns) over shorter ones

# Tags

- String Manipulation
- Parsing
- Character Encoding/Decoding
- Two Pointers
- Greedy Algorithm

