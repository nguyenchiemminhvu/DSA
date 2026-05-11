## Problem

https://leetcode.com/problems/edit-distance/description/

````markdown
## Problem

https://leetcode.com/problems/edit-distance/description/

Given two strings `word1` and `word2`, return the **minimum number of operations** required to convert `word1` to `word2`.

You have the following three operations permitted on a word:
- **Insert** a character
- **Delete** a character
- **Replace** a character

**Example 1:**
```
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation:
horse -> rorse (replace 'h' with 'r')
rorse -> rose  (delete 'r')
rose  -> ros   (delete 'e')
```

**Example 2:**
```
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation:
intention -> inention  (delete 't')
inention  -> enention  (replace 'i' with 'e')
enention  -> exention  (replace 'n' with 'x')
exention  -> exection  (replace 'n' with 'c')
exection  -> execution (insert 'u')
```

**Constraints:**
- `0 <= word1.length, word2.length <= 500`
- `word1` and `word2` consist of lowercase English letters.

## Observations

- This is the classic **Edit Distance** (Levenshtein Distance) problem.
- At any position `(i1, i2)` representing a suffix of `word1` starting at `i1` and a suffix of `word2` starting at `i2`, we face a choice:
  - If `word1[i1] == word2[i2]`: no operation needed — advance both pointers.
  - Otherwise, we try all three operations and take the minimum:
    - **Replace**: cost 1, then advance both pointers → `1 + F(i1+1, i2+1)`
    - **Insert** (into `word1`): cost 1, advance `i2` only → `1 + F(i1, i2+1)`
    - **Delete** (from `word1`): cost 1, advance `i1` only → `1 + F(i1+1, i2)`
- **Base cases**:
  - If we exhaust `word1` (`i1 == n1`): we need `n2 - i2` insertions to match the remaining characters of `word2`.
  - If we exhaust `word2` (`i2 == n2`): we need `n1 - i1` deletions to remove the remaining characters of `word1`.
- The subproblem structure has overlapping subproblems → classic candidate for **memoization** or **bottom-up DP**.
- The total number of unique states is `O(n1 × n2)`, giving overall **time complexity O(n1 × n2)** and **space complexity O(n1 × n2)**.

## Solution

The solution uses a 2D DP table `dp[i1][i2]` representing the minimum edit distance between `word1[i1:]` and `word2[i2:]`.

**Initialization:**
- `dp[i][n2] = n1 - i` — need to delete all remaining characters of `word1`.
- `dp[n1][i] = n2 - i` — need to insert all remaining characters of `word2`.

**Recurrence (filled bottom-up, from `n1-1` to `0` and `n2-1` to `0`):**
```
if word1[i1] == word2[i2]:
    dp[i1][i2] = dp[i1+1][i2+1]          # no operation needed
else:
    dp[i1][i2] = 1 + min(
        dp[i1+1][i2+1],   # replace
        dp[i1][i2+1],     # insert
        dp[i1+1][i2]      # delete
    )
```

**Answer:** `dp[0][0]`

```python
class Solution:
    def minDistance(self, s1: str, s2: str) -> int:
        n1 = len(s1)
        n2 = len(s2)

        # mem = {}
        # def F(i1: int, i2: int) -> int:
        #     if i1 >= n1:
        #         return max(0, n2 - i2) # need insert operations
        #     if i2 >= n2:
        #         return max(0, n1 - i1) # need delete operations

        #     if (i1, i2) in mem:
        #         return mem[(i1, i2)]

        #     res = float('inf')
        #     if s1[i1] == s2[i2]:
        #         res = F(i1 + 1, i2 + 1)
        #     else:
        #         op1 = 1 + F(i1 + 1, i2 + 1) # move on with sub operation
        #         op2 = 1 + F(i1, i2 + 1) # move on with ins operation
        #         op3 = 1 + F(i1 + 1, i2) # move on with del operation
        #         res = min([op1, op2, op3])
        #     mem[(i1, i2)] = res
        #     return res
        
        # return F(0, 0)

        dp = [[float('inf') for _ in range(n2 + 1)] for _ in range(n1 + 1)]
        for i in range(n1 + 1):
            dp[i][n2] = n1 - i
        for i in range(n2 + 1):
            dp[n1][i] = n2 - i
        
        for i1 in range(n1 - 1, -1, -1):
            for i2 in range(n2 - 1, -1, -1):
                if s1[i1] == s2[i2]:
                    dp[i1][i2] = dp[i1 + 1][i2 + 1]
                else:
                    dp[i1][i2] = min([
                        1 + dp[i1 + 1][i2 + 1],
                        1 + dp[i1][i2 + 1],
                        1 + dp[i1 + 1][i2]
                    ])
        
        return dp[0][0]
```

**Complexity:**
- Time: `O(n1 × n2)`
- Space: `O(n1 × n2)` — can be optimized to `O(min(n1, n2))` by using two 1D arrays since each row only depends on the next row.

# Tags
- Dynamic Programming
- String
- Bottom-up DP
- Memoization
````

## Observations

## Solution

# Tags

