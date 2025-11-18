## Problem

https://leetcode.com/problems/check-if-numbers-are-ascending-in-a-sentence/description/

```
A sentence is a list of tokens separated by a single space with no leading or trailing spaces. Every token is either a positive number consisting of digits 0-9 with no leading zeros, or a word consisting of lowercase English letters.

For example, "a puppy has 2 eyes 4 legs" is a sentence with seven tokens: "2" and "4" are numbers and the other tokens such as "puppy" are words.
Given a string s representing a sentence, you need to check if all the numbers in s are strictly increasing from left to right (i.e., other than the last number, each number is strictly smaller than the number on its right in s).

Return true if so, or false otherwise.

Example 1:

example-1
Input: s = "1 box has 3 blue 4 red 6 green and 12 yellow marbles"
Output: true
Explanation: The numbers in s are: 1, 3, 4, 6, 12.
They are strictly increasing from left to right: 1 < 3 < 4 < 6 < 12.
Example 2:

Input: s = "hello world 5 x 5"
Output: false
Explanation: The numbers in s are: 5, 5. They are not strictly increasing.

Example 3:

example-3
Input: s = "sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"
Output: false
Explanation: The numbers in s are: 7, 51, 50, 60. They are not strictly increasing.

Constraints:

3 <= s.length <= 200
s consists of lowercase English letters, spaces, and digits from 0 to 9, inclusive.
The number of tokens in s is between 2 and 100, inclusive.
The tokens in s are separated by a single space.
There are at least two numbers in s.
Each number in s is a positive number less than 100, with no leading zeros.
s contains no leading or trailing spaces.
```

## Observations

1. **Number Extraction Challenge**: We need to parse numbers from a mixed string containing words and digits
2. **Multi-digit Numbers**: Numbers can have multiple digits (like "12", "51"), so we can't process single characters
3. **Strictly Increasing**: The condition is strict inequality (a < b), not (a ≤ b)
4. **Boundary Handling**: We need to properly detect when a number ends (space or end of string)
5. **Edge Cases**: 
   - Same numbers appearing twice (should return false)
   - Single digit vs multi-digit numbers
   - Numbers at the beginning/end of sentence

## Solution

### Approach: Number Extraction + Validation

The solution uses a **two-phase approach**:

**Phase 1: Extract all numbers from the sentence**
- Iterate through each character
- Build numbers digit by digit when encountering digits
- Store complete numbers when hitting non-digit characters

**Phase 2: Check if extracted numbers are strictly ascending**
- Compare each number with the previous one
- Return false if any number ≤ previous number

### Key Insights

1. **Smart Boundary Handling**: Adding a space `s += ' '` ensures the last number gets processed
2. **Number Building**: `val = val * 10 + int(c)` correctly handles multi-digit numbers
3. **Reset Logic**: `val = 0` after storing ensures we start fresh for the next number
4. **Validation Check**: `val > 0` prevents storing empty numbers from consecutive spaces

### Trace Through Example

Input: `"1 box has 3 blue 4"`

```
Character | Action              | val | arr
---------|---------------------|-----|----------
'1'      | Build number        | 1   | []
' '      | Store & reset       | 0   | [1]
'b','o','x',' ' | Skip letters   | 0   | [1]
'3'      | Build number        | 3   | [1]
' '      | Store & reset       | 0   | [1, 3]
...      | Skip letters        | 0   | [1, 3]
'4'      | Build number        | 4   | [1, 3]
' '      | Store & reset       | 0   | [1, 3, 4]
```

Final check: `1 < 3 < 4` → Return `true`

### Time & Space Complexity
- **Time**: O(n) - single pass through string + single pass through numbers
- **Space**: O(k) - where k is the number of integers in the sentence

# Tags

- **String Processing**: Parsing mixed content (numbers + text)
- **Array**: Storing and comparing sequences
- **Two Pointers**: Comparing adjacent elements
- **Parsing**: Number extraction from text

## Alternative Solutions

### Approach 2: Regular Expressions
```python
import re
class Solution:
    def areNumbersAscending(self, s: str) -> bool:
        numbers = [int(x) for x in re.findall(r'\d+', s)]
        return all(numbers[i] < numbers[i+1] for i in range(len(numbers)-1))
```

### Approach 3: Split and Filter
```python
class Solution:
    def areNumbersAscending(self, s: str) -> bool:
        tokens = s.split()
        numbers = [int(token) for token in tokens if token.isdigit()]
        return all(numbers[i] < numbers[i+1] for i in range(len(numbers)-1))
```

**Why the main solution is preferred:**
- More explicit control over parsing logic
- No regex dependency
- Handles edge cases more clearly
- Educational value for understanding string processing

