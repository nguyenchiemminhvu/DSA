## Problem

https://leetcode.com/problems/maximum-score-after-splitting-a-string/description/

```
Given a string s of zeros and ones, return the maximum score after splitting the string into two non-empty substrings (i.e. left substring and right substring).

The score after splitting a string is the number of zeros in the left substring plus the number of ones in the right substring.

Example 1:

Input: s = "011101"
Output: 5 
Explanation: 
All possible ways of splitting s into two non-empty substrings are:
left = "0" and right = "11101", score = 1 + 4 = 5 
left = "01" and right = "1101", score = 1 + 3 = 4 
left = "011" and right = "101", score = 1 + 2 = 3 
left = "0111" and right = "01", score = 1 + 1 = 2 
left = "01110" and right = "1", score = 2 + 1 = 3

Example 2:

Input: s = "00111"
Output: 5
Explanation: When left = "00" and right = "111", we get the maximum score = 2 + 3 = 5

Example 3:

Input: s = "1111"
Output: 3

Constraints:

2 <= s.length <= 500
The string s consists of characters '0' and '1' only.
```

## Observations

1. **Problem Understanding**: We need to split a binary string into two non-empty parts and maximize the score where:
   - Score = (number of zeros in left part) + (number of ones in right part)

2. **Key Insights**:
   - We can split at any position from index 0 to len(s)-2 (to ensure both parts are non-empty)
   - For each split at position i:
     - Left part: s[0:i+1] - count zeros here
     - Right part: s[i+1:] - count ones here

3. **Mathematical Observation**:
   - Total ones in string = constant
   - For split at position i: zeros_left + ones_right = zeros_left + (total_ones - ones_left)
   - This can be rewritten as: (length_left - ones_left) + (total_ones - ones_left)
   - Simplifying: length_left + total_ones - 2 * ones_left
   - So we want to minimize ones_left to maximize the score

4. **Code Analysis**:
   - The given solution uses a clever mathematical transformation
   - Instead of counting zeros and ones separately, it uses the formula above
   - `i + 1 - left + right` represents: (length_left) - (ones_left) + (ones_right)

## Solution

1. **Initialization**: Convert string to integer array and calculate total ones
2. **Iteration**: For each valid split position i:
   - Update running sum of ones in left part
   - Calculate ones in right part = total_ones - ones_in_left
   - Calculate score = zeros_in_left + ones_in_right
   - Where zeros_in_left = (i+1) - ones_in_left
3. **Formula**: Score = (i+1) - ones_left + ones_right = (i+1) - left + (s - left)

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(n) - for the prefix array (can be optimized to O(1))

**Example Walkthrough** with s = "011101":
- Total ones = 4
- Split at i=0: left="0", right="11101" → score = 1 + 4 = 5
- Split at i=1: left="01", right="1101" → score = 1 + 3 = 4
- Split at i=2: left="011", right="101" → score = 1 + 2 = 3
- And so on...

The algorithm efficiently finds the maximum score of 5.

# Tags

- String
- Prefix Sum
- Greedy
- Math
- Array

