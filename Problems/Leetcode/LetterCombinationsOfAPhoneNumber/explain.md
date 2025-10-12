## Problem

https://leetcode.com/problems/letter-combinations-of-a-phone-number/

```
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:

Input: digits = ""
Output: []

Example 3:

Input: digits = "2"
Output: ["a","b","c"]

Constraints:

0 <= digits.length <= 4
digits[i] is a digit in the range ['2', '9'].
```

## Observations

1. **Problem Pattern**: This is a classic backtracking problem where we need to generate all possible combinations from multiple sets of choices.

2. **Phone Button Mapping**: 
   - Digits 2-9 map to letters like on old phone keypads
   - Digit 2 → "abc", 3 → "def", 4 → "ghi", 5 → "jkl", 6 → "mno", 7 → "pqrs", 8 → "tuv", 9 → "wxyz"
   - Digits 0 and 1 don't map to any letters

3. **Key Insights**:
   - For each digit, we have multiple letter choices
   - We need to explore all combinations: if digits = "23", we try all combinations of letters from digit 2 with letters from digit 3
   - This forms a decision tree where each level represents a digit position
   - At each node, we branch into all possible letter choices for that digit

4. **Edge Cases**:
   - Empty string input should return empty array
   - Single digit should return all letters for that digit
   - Maximum 4 digits means at most 4^4 = 256 combinations (worst case with digit 7 or 9)

## Solution

The solution uses **backtracking** with depth-first search (DFS):

### Algorithm Breakdown:

1. **Setup**:
   - `text` array maps digit indices to their corresponding letters
   - `res` stores final combinations
   - `temp` stores current combination being built

2. **DFS Function**:
   - **Base Case**: When `i == n` (processed all digits), add current combination to results
   - **Recursive Case**: For current digit position `i`:
     - Get the digit value and find corresponding letters
     - Try each letter: add to `temp`, recurse, then backtrack (remove from `temp`)

3. **Backtracking Process**:
   ```
   digits = "23"
   
   Level 0 (digit '2'): try 'a', 'b', 'c'
   ├── 'a' → Level 1 (digit '3'): try 'd', 'e', 'f'
   │   ├── 'ad' ✓
   │   ├── 'ae' ✓  
   │   └── 'af' ✓
   ├── 'b' → Level 1 (digit '3'): try 'd', 'e', 'f'
   │   ├── 'bd' ✓
   │   ├── 'be' ✓
   │   └── 'bf' ✓
   └── 'c' → Level 1 (digit '3'): try 'd', 'e', 'f'
       ├── 'cd' ✓
       ├── 'ce' ✓
       └── 'cf' ✓
   ```

### Time & Space Complexity:
- **Time**: O(3^N × 4^M) where N = digits mapped to 3 letters, M = digits mapped to 4 letters
- **Space**: O(3^N × 4^M) for storing results + O(digits.length) for recursion stack

### Key Implementation Details:
- `ord(digits[i]) - ord('0')` converts character digit to integer index
- `"".join(temp)` efficiently creates string from character list
- The condition `if len(temp) > 0` handles empty input case

## Tags

array, string, backtracking