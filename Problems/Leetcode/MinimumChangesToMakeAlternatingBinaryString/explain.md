## Problem

https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/description/

```
You are given a string s consisting only of the characters '0' and '1'. In one operation, you can change any '0' to '1' or vice versa.

The string is called alternating if no two adjacent characters are equal. For example, the string "010" is alternating, while the string "0100" is not.

Return the minimum number of operations needed to make s alternating.

Example 1:

Input: s = "0100"
Output: 1
Explanation: If you change the last character to '1', s will be "0101", which is alternating.

Example 2:

Input: s = "10"
Output: 0
Explanation: s is already alternating.

Example 3:

Input: s = "1111"
Output: 2
Explanation: You need two operations to reach "0101" or "1010".

Constraints:

1 <= s.length <= 104
s[i] is either '0' or '1'.
```

## Observations

1. **Only Two Possible Alternating Patterns**: For any string length n, there are exactly two possible alternating patterns:
   - Pattern 1: "010101..." (starts with '0')
   - Pattern 2: "101010..." (starts with '1')

2. **Optimal Strategy**: Since we can only flip characters (0→1 or 1→0), we need to find which of the two patterns requires fewer changes.

3. **Character Position Rule**: In an alternating string:
   - Even indices (0, 2, 4, ...) should have the same character
   - Odd indices (1, 3, 5, ...) should have the same character
   - Adjacent characters must be different

4. **Cost Calculation**: For each pattern, count how many characters in the input string differ from the target pattern.

## Solution

**Approach**: Greedy comparison with both possible alternating patterns.

**Algorithm**:
1. Generate both possible alternating patterns for the given string length
2. Compare the input string character by character with each pattern
3. Count mismatches (operations needed) for each pattern
4. Return the minimum cost

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(n) - for storing the pattern strings (can be optimized to O(1))

**Key Insights**:
- We don't need to actually perform the operations, just count them
- The optimal solution is always one of the two alternating patterns
- Pattern generation using string multiplication: `'01' * n` creates "010101..."

**Example Walkthrough** (s = "0100"):
- Pattern 1 ("0101"): positions 3 differs → cost1 = 1
- Pattern 2 ("1010"): positions 0, 2, 3 differ → cost2 = 3
- Return min(1, 3) = 1

# Tags
String, Greedy, Pattern Matching

