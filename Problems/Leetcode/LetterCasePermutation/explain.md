## Problem

https://leetcode.com/problems/letter-case-permutation/description/

```
Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.

Return a list of all possible strings we could create. Return the output in any order.

Example 1:
Input: s = "a1b2"
Output: ["a1b2","a1B2","A1b2","A1B2"]

Example 2:
Input: s = "3z4"
Output: ["3z4","3Z4"]

Constraints:
- 1 <= s.length <= 12
- s consists of lowercase English letters, uppercase English letters, and digits.
```

## Observations

1. **Problem Type**: This is a permutation generation problem where we need to explore all possible combinations of letter cases.

2. **Key Insights**:
   - Digits remain unchanged (only one possibility per digit)
   - Letters can be either lowercase or uppercase (two possibilities per letter)
   - For a string with `k` letters, there will be `2^k` possible permutations
   - This is a classic backtracking problem where we make choices at each position

3. **Approach**: Use backtracking/DFS to generate all permutations:
   - For each character position, make a decision
   - If it's a digit, only one choice: keep it as is
   - If it's a letter, two choices: lowercase or uppercase
   - Recursively generate permutations for the remaining string

4. **Time Complexity**: O(2^n × n) where n is the length of the string
   - We generate 2^k permutations (k = number of letters)
   - Each permutation takes O(n) time to construct
   
5. **Space Complexity**: O(n) for the recursion stack and temporary array (not counting the output)

## Solution

```python
class Solution:
    def letterCasePermutation(self, s: str) -> List[str]:
        n = len(s)
        res = []
        tmp = []
        
        def generating(idx: int) -> None:
            # Base case: we've processed all characters
            if idx >= n:
                res.append("".join(tmp))
                return
            
            c = s[idx]
            
            # If it's a digit, only one choice
            if c.isdigit():
                tmp.append(s[idx])
                generating(idx + 1)
                tmp.pop()
            else:
                # If it's a letter, try both lowercase and uppercase
                # Choice 1: lowercase
                tmp.append(s[idx].lower())
                generating(idx + 1)
                tmp.pop()

                # Choice 2: uppercase
                tmp.append(s[idx].upper())
                generating(idx + 1)
                tmp.pop()
        
        generating(0)
        return res
```

**How it works**:

1. **Initialization**: 
   - `res`: stores all generated permutations
   - `tmp`: temporary array to build current permutation
   - `n`: length of input string

2. **Backtracking Function** (`generating`):
   - **Base Case**: When `idx >= n`, we've built a complete permutation, so join `tmp` and add to `res`
   
   - **Digit Case**: If current character is a digit, append it to `tmp`, recurse to next position, then backtrack (pop)
   
   - **Letter Case**: If current character is a letter, explore both possibilities:
     - First, try lowercase version: append, recurse, backtrack
     - Then, try uppercase version: append, recurse, backtrack

3. **Decision Tree Example** for "a1b":
   ```
                    ""
                    |
                   "a"
                    |
                  "a1"
                 /    \
              "a1b"  "a1B"
   ```
   But actually it branches at 'a' too:
   ```
                      ""
                    /    \
                  "a"    "A"
                  |       |
                "a1"    "A1"
                /  \    /  \
            "a1b" "a1B" "A1b" "A1B"
   ```

4. **Key Points**:
   - The backtracking pattern: append → recurse → pop (undo)
   - This ensures we explore all branches of the decision tree
   - Digits reduce branching factor (only 1 choice instead of 2)
   - The order of lowercase/uppercase doesn't matter for correctness

# Tags

