## Problem

https://leetcode.com/problems/construct-smallest-number-from-di-string/description/

```
You are given a 0-indexed string pattern of length n consisting of the characters 'I' meaning increasing and 'D' meaning decreasing.

A 0-indexed string num of length n + 1 is created using the following conditions:

num consists of the digits '1' to '9', where each digit is used at most once.
If pattern[i] == 'I', then num[i] < num[i + 1].
If pattern[i] == 'D', then num[i] > num[i + 1].
Return the lexicographically smallest possible string num that meets the conditions.

Example 1:

Input: pattern = "IIIDIDDD"
Output: "123549876"
Explanation:
At indices 0, 1, 2, and 4 we must have that num[i] < num[i+1].
At indices 3, 5, 6, and 7 we must have that num[i] > num[i+1].
Some possible values of num are "245639871", "135749862", and "123849765".
It can be proven that "123549876" is the smallest possible num that meets the conditions.
Note that "123414321" is not possible because the digit '1' is used more than once.

Example 2:

Input: pattern = "DDD"
Output: "4321"
Explanation:
Some possible values of num are "9876", "7321", and "8742".
It can be proven that "4321" is the smallest possible num that meets the conditions.

Constraints:

1 <= pattern.length <= 8
pattern consists of only the letters 'I' and 'D'.
```

## Observations

1. **Problem Structure**: We need to construct a number using digits 1-9 (each at most once) where the pattern dictates relationships between adjacent digits.

2. **Pattern Interpretation**: 
   - 'I' means the next digit must be greater than the current one
   - 'D' means the next digit must be smaller than the current one

3. **Key Constraints**:
   - Pattern length `n` means we need `n+1` digits in our result
   - Each digit 1-9 can be used at most once
   - We want the lexicographically smallest valid number

4. **Brute Force Approach**: The given solution uses backtracking to generate all possible valid combinations and then selects the minimum one.

5. **Search Space**: With digits 1-9 and pattern length up to 8, we have at most 9 positions to fill, making the search space manageable for backtracking.

## Solution

### Approach: Backtracking with All Candidates Generation

1. **Initialization**: Start with empty `temp` array and `visited` set
2. **DFS Traversal**: For each position, try digits 1-9
3. **Constraint Checking**: 
   - For 'I': ensure next digit > current digit
   - For 'D': ensure next digit < current digit
4. **Backtracking**: Add/remove digits and update visited set
5. **Result Selection**: From all valid candidates, return the lexicographically smallest

### Time Complexity: 
- Worst case: O(9!) for generating all permutations, but pruning reduces this significantly
- Space: O(n) for recursion depth and temporary storage

### Issues with Current Solution:
1. **Inefficient**: Generates ALL valid solutions instead of finding the optimal one directly
2. **Memory Usage**: Stores all candidates which is unnecessary
3. **Starting Index**: Using `dfs(-1)` is confusing - should start with `dfs(0)`

### Better Approach:
A more efficient solution would use greedy construction or direct backtracking to find the lexicographically smallest number without generating all candidates.

## Tags

array, string, backtracking