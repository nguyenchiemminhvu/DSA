## Problem

https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/

```
You are given two strings s1 and s2 of equal length consisting of letters "x" and "y" only. Your task is to make these two strings equal to each other. You can swap any two characters that belong to different strings, which means: swap s1[i] and s2[j].

Return the minimum number of swaps required to make s1 and s2 equal, or return -1 if it is impossible to do so.

Example 1:

Input: s1 = "xx", s2 = "yy"
Output: 1
Explanation: Swap s1[0] and s2[1], s1 = "yx", s2 = "yx".

Example 2:

Input: s1 = "xy", s2 = "yx"
Output: 2
Explanation: Swap s1[0] and s2[0], s1 = "yy", s2 = "xx".
Swap s1[0] and s2[1], s1 = "xy", s2 = "xy".
Note that you cannot swap s1[0] and s1[1] to make s1 equal to "yx", cause we can only swap chars in different strings.

Example 3:

Input: s1 = "xx", s2 = "xy"
Output: -1

Constraints:

1 <= s1.length, s2.length <= 1000
s1.length == s2.length
s1, s2 only contain 'x' or 'y'.
```

## Observations

1. **Only mismatched positions matter**: We only need to consider positions where `s1[i] != s2[i]`, since positions where they're already equal don't need any swaps.

2. **Two types of mismatches**: 
   - Type 1: `s1[i] = 'x'` and `s2[i] = 'y'` (xy pairs)
   - Type 2: `s1[i] = 'y'` and `s2[i] = 'x'` (yx pairs)

3. **Parity constraint**: For the strings to be made equal, the total number of mismatched positions must be even. This is because each swap fixes exactly 2 mismatched positions.

4. **Optimal swapping strategy**:
   - **Same type pairs**: Two xy pairs can be fixed with 1 swap, two yx pairs can be fixed with 1 swap
   - **Different type pairs**: One xy pair + one yx pair can be fixed with 2 swaps

## Solution

### Algorithm Steps:

1. **Count mismatches**: Count how many xy and yx pairs we have.
2. **Check feasibility**: If the total number of mismatches is odd, it's impossible to make the strings equal (return -1).
3. **Calculate minimum swaps**:
   - `count_x_y // 2`: Each pair of xy mismatches needs 1 swap
   - `count_y_x // 2`: Each pair of yx mismatches needs 1 swap  
   - `(count_x_y % 2) + (count_y_x % 2)`: Remaining unpaired mismatches need 2 swaps each

### Examples Walkthrough:

**Example 1**: `s1 = "xx"`, `s2 = "yy"`
- count_x_y = 2, count_y_x = 0
- Total mismatches = 2 (even) ✓
- Swaps = 2//2 + 0//2 + (2%2) + (0%2) = 1 + 0 + 0 + 0 = 1

**Example 2**: `s1 = "xy"`, `s2 = "yx"`  
- count_x_y = 1, count_y_x = 1
- Total mismatches = 2 (even) ✓
- Swaps = 1//2 + 1//2 + (1%2) + (1%2) = 0 + 0 + 1 + 1 = 2

**Example 3**: `s1 = "xx"`, `s2 = "xy"`
- count_x_y = 1, count_y_x = 0
- Total mismatches = 1 (odd) → return -1

**Time Complexity**: O(n) where n is the length of the strings  
**Space Complexity**: O(1) - only using a few variables

The solution is elegant because it recognizes that we can optimally pair mismatches of the same type (requiring 1 swap per pair) and handle remaining mixed pairs (requiring 2 swaps each).

## Tags

array, string, greedy