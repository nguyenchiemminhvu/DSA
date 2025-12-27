## Problem

https://leetcode.com/problems/score-of-parentheses/description/

```
Given a balanced parentheses string s, return the score of the string.

The score of a balanced parentheses string is based on the following rule:

- "()" has score 1.
- AB has score A + B, where A and B are balanced parentheses strings.
- (A) has score 2 * A, where A is a balanced parentheses string.

Example 1:
Input: s = "()"
Output: 1

Example 2:
Input: s = "(())"
Output: 2

Example 3:
Input: s = "()()"
Output: 2

Constraints:
- 2 <= s.length <= 50
- s consists of only '(' and ')'.
- s is a balanced parentheses string.
```

## Observations

1. **Recursive Scoring Structure**: The problem defines scoring rules that are inherently recursive:
   - Base case: `()` = 1
   - Concatenation: `AB` = A + B
   - Nesting: `(A)` = 2 * A

2. **Nesting Level Matters**: Each level of nesting doubles the score. For example:
   - `()` = 1 (level 0)
   - `(())` = 2 (level 1)
   - `((()))` = 4 (level 2)

3. **Key Insight**: We only need to count the score when we encounter a complete `()` pair. The score contribution of each `()` is `2^level`, where `level` is the current nesting depth.

4. **Pattern Recognition**: When we see `)(` in the string, the `)` closes a nested structure, but when we see `()`, it's a base unit that contributes to the score based on its nesting level.

## Solution

### Approach: Level-Based Scoring

The solution uses a single pass through the string, tracking the nesting level and adding scores only when encountering `()` pairs.

**Algorithm:**
1. Maintain a `level` counter to track current nesting depth
2. For each character:
   - If `(`: increment level (going deeper)
   - If `)`: 
     - Decrement level (coming out)
     - Check if previous character was `(` (forming a `()` pair)
     - If yes, add `2^level` to the score (using bit shift `1 << level`)

**Why this works:**
- Each `()` at nesting level `n` contributes `2^n` to the total score
- The nesting level when we encounter `)` represents how many layers deep the `()` is
- All `()` pairs at the same level simply add up (concatenation rule)
- The doubling effect of nesting is captured by `2^level`

```python
class Solution:
    def scoreOfParentheses(self, s: str) -> int:
        score = 0
        level = 0
        for i in range(len(s)):
            if s[i] == '(':
                level += 1
            else:
                level -= 1
                if s[i - 1] == '(':
                    score += (1 << level)
        return score
```

**Example Trace for `"(()())"`:**
- i=0: `(` → level=1
- i=1: `(` → level=2
- i=2: `)` → level=1, prev='(' → score += 2¹ = 2
- i=3: `(` → level=2
- i=4: `)` → level=1, prev='(' → score += 2¹ = 2
- i=5: `)` → level=0, prev=')'
- **Result: 2 + 2 = 4**

**Time Complexity:** O(n) - single pass through the string  
**Space Complexity:** O(1) - only constant extra space

# Tags
#stack #string #parentheses #bit-manipulation #greedy

