## Problem

https://leetcode.com/problems/maximum-score-from-removing-substrings/description/

```
You are given a string s and two integers x and y. You can perform two types of operations any number of times.

1. Remove substring "ab" and gain x points.
   - For example, when removing "ab" from "cabxbae" it becomes "cxbae".
2. Remove substring "ba" and gain y points.
   - For example, when removing "ba" from "cabxbae" it becomes "cabxe".

Return the maximum points you can gain after applying the above operations on s.

Example 1:
Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19
Explanation:
- Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
- Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
- Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
- Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.

Example 2:
Input: s = "aabbaaxybbaabb", x = 5, y = 4
Output: 20

Constraints:
- 1 <= s.length <= 10^5
- 1 <= x, y <= 10^4
- s consists of lowercase English letters.
```

## Observations

1. **Greedy Strategy**: The key insight is to remove the higher-scoring pattern first, then remove the lower-scoring pattern from what remains. This greedy approach is optimal because:
   - Removing one pattern doesn't create the other pattern (removing "ab" can't create "ba" and vice versa)
   - Each removal is independent and doesn't block future removals

2. **Order Matters**: If x > y, prioritize removing "ab" first. If y > x, prioritize removing "ba" first. This ensures we maximize points by getting as many high-value removals as possible.

3. **Stack-Based Removal**: We can use a stack to efficiently remove patterns in a single pass:
   - For each character, check if it forms the target pattern with the top of the stack
   - If yes, pop the stack and add the score
   - If no, push the character onto the stack

4. **Two-Pass Solution**: After removing the higher-scoring pattern, we need a second pass to remove the lower-scoring pattern from the remaining string.

## Solution

```python
class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        def remove(s:str, pattern:str, score:int) -> Tuple[str]:
            st = []
            sum_score = 0
            for c in s:
                if c != pattern[1]:
                    st.append(c)
                else:
                    if st and st[-1] == pattern[0]:
                        sum_score += score
                        st.pop()
                    else:
                        st.append(c)
            return ("".join(st), str(sum_score))
        
        if x > y:
            s, score1 = remove(s, 'ab', x)
            s, score2 = remove(s, 'ba', y)
            return int(score1) + int(score2)
        else:
            s, score1 = remove(s, 'ba', y)
            s, score2 = remove(s, 'ab', x)
            return int(score1) + int(score2)
```

**Algorithm Explanation**:

1. **Helper Function `remove(s, pattern, score)`**:
   - Uses a stack to process the string character by character
   - When encountering the second character of the pattern:
     - Check if the top of stack is the first character of the pattern
     - If yes: we found the pattern! Pop the stack and add the score
     - If no: just push the current character
   - If the character is not the second character of the pattern, simply push it
   - Returns the remaining string (after removals) and the total score

2. **Main Logic**:
   - Determine which pattern to remove first based on which has higher score
   - First pass: Remove the higher-scoring pattern and accumulate points
   - Second pass: Remove the lower-scoring pattern from the remaining string
   - Return the sum of both scores

**Complexity Analysis**:
- Time: O(n) where n is the length of string s. We process each character at most twice.
- Space: O(n) for the stack in the worst case when no patterns can be removed.

**Why Greedy Works**:
The greedy approach of removing the higher-scoring pattern first is optimal because:
- Each removal is independent - we don't block future removals
- Removing "ab" or "ba" doesn't create new instances of the other pattern
- By maximizing higher-value removals first, we guarantee the maximum total score

# Tags
`greedy` `stack` `string` `two-pointer`

