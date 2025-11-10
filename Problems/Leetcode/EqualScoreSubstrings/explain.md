## Problem

https://leetcode.com/problems/equal-score-substrings/description/

```
You are given a string s consisting of lowercase English letters.

The score of a string is the sum of the positions of its characters in the alphabet, where 'a' = 1, 'b' = 2, ..., 'z' = 26.

Determine whether there exists an index i such that the string can be split into two non-empty substrings s[0..i] and s[(i + 1)..(n - 1)] that have equal scores.

Return true if such a split exists, otherwise return false.

Example 1:

Input: s = "adcb"

Output: true

Explanation:

Split at index i = 1:

Left substring = s[0..1] = "ad" with score = 1 + 4 = 5
Right substring = s[2..3] = "cb" with score = 3 + 2 = 5
Both substrings have equal scores, so the output is true.

Example 2:

Input: s = "bace"

Output: false

Explanation:​​​​​​

​​​​​​​No split produces equal scores, so the output is false.

Constraints:

2 <= s.length <= 100
s consists of lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to find if there's a way to split the string into two non-empty parts with equal scores, where score = sum of character positions in alphabet ('a'=1, 'b'=2, etc.).

2. **Key Insights**:
   - For each possible split position `i`, we have left part `s[0..i]` and right part `s[i+1..n-1]`
   - We need to check if `score(left) == score(right)`
   - Since we need non-empty parts, valid split positions are from 0 to n-2 (inclusive)

3. **Brute Force Approach**: Calculate scores for left and right parts at each split position
   - Time: O(n²) - for each split, we sum up characters
   - Space: O(1)

4. **Optimized Approach**: Use prefix sum technique
   - Pre-calculate total sum once
   - For each split, maintain running left sum and calculate right sum as `total - left`
   - Time: O(n), Space: O(n) for storing character values

## Solution

### Approach: Prefix Sum Optimization

The solution uses an efficient prefix sum approach:

1. **Convert characters to values**: `prefix = [ord(c) - ord('a') + 1 for c in s]`
   - Converts each character to its alphabet position (a=1, b=2, ..., z=26)

2. **Calculate total sum**: `total = sum(prefix)`
   - Get the sum of all character values in the string

3. **Try each split position**:
   - Maintain `left` sum as running total
   - Calculate `right` sum as `total - left`
   - Check if `left == right` at any position

4. **Return result**: True if equal split found, False otherwise

### Example Walkthrough:
For `s = "adcb"`:
- Character values: [1, 4, 3, 2]
- Total sum: 10
- Split attempts:
  - i=0: left=1, right=9 → not equal
  - i=1: left=5, right=5 → equal! Return True

### Complexity:
- **Time**: O(n) - single pass through the string
- **Space**: O(n) - storing character values in prefix array

### Alternative Space-Optimized Version:
Could be optimized to O(1) space by calculating values on-the-fly without storing the prefix array.

# Tags

- Array
- Prefix Sum
- String
- Two Pointers

