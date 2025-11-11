## Problem

https://leetcode.com/problems/ones-and-zeroes/description/

```
You are given an array of binary strings strs and two integers m and n.

Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset.

A set x is a subset of a set y if all elements of x are also elements of y. 

Example 1:

Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
Output: 4
Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
{"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.

Example 2:

Input: strs = ["10","0","1"], m = 1, n = 1
Output: 2
Explanation: The largest subset is {"0", "1"}, so the answer is 2.

Constraints:

1 <= strs.length <= 600
1 <= strs[i].length <= 100
strs[i] consists only of digits '0' and '1'.
1 <= m, n <= 100
```

## Observations

1. **Problem Nature**: This is a **3D Dynamic Programming** problem that combines aspects of:
   - **0/1 Knapsack Problem**: Each string can be either included or excluded
   - **Multiple Constraints**: We have two weight constraints (m zeros and n ones)
   - **Subset Selection**: We want to maximize the count of strings, not their value

2. **Key Insights**:
   - **State Definition**: For each string, we have three choice parameters:
     - Current index in the strings array
     - Remaining capacity for zeros (m_left)
     - Remaining capacity for ones (n_left)
   - **Decision Making**: At each string, we can either:
     - **Skip** the current string (move to next index)
     - **Take** the current string (if it doesn't exceed our constraints)

3. **Constraint Analysis**:
   - Each string has a "cost" in terms of zeros and ones it contains
   - We must ensure: `zeros_needed <= m_left` and `ones_needed <= n_left`
   - The goal is to maximize the **count** of strings selected, not minimize cost

4. **Recursive Structure**:
   - **Base Case**: If we've processed all strings, return 0
   - **Choice 1**: Skip current string → `F(idx + 1, m_left, n_left)`
   - **Choice 2**: Take current string (if feasible) → `1 + F(idx + 1, m_left - zeros, n_left - ones)`
   - **Result**: Take maximum of both choices

5. **Optimization Opportunities**:
   - **Memoization**: Cache results for `(idx, m_left, n_left)` combinations
   - **Preprocessing**: Count zeros and ones for each string once
   - **Bottom-up DP**: Can be converted to iterative 3D DP table

## Solution

The solution uses **Top-Down Dynamic Programming (Recursion + Memoization)**:

### Algorithm Breakdown:

1. **Preprocessing**:
   ```python
   counts = [(s.count('0'), s.count('1')) for s in strs]
   ```
   - Pre-calculate zero and one counts for each string for O(1) lookup

2. **Memoization Setup**:
   ```python
   self.memo = {}
   ```
   - Cache results to avoid recomputing same subproblems

3. **Recursive Function `F(idx, m_left, n_left)`**:
   - **Parameters**:
     - `idx`: Current string index being considered
     - `m_left`: Remaining zeros we can use
     - `n_left`: Remaining ones we can use
   - **Returns**: Maximum number of strings we can select from `strs[idx:]`

4. **Base Case**:
   ```python
   if idx >= len(strs):
       return 0
   ```
   - If we've processed all strings, no more can be selected

5. **Memoization Check**:
   ```python
   if (idx, m_left, n_left) in self.memo:
       return self.memo[(idx, m_left, n_left)]
   ```
   - Return cached result if already computed

6. **Decision Logic**:
   ```python
   # Option 1: Skip current string
   res = F(idx + 1, m_left, n_left)
   
   # Option 2: Take current string (if possible)
   zeros, ones = counts[idx]
   if m_left >= zeros and n_left >= ones:
       res = max(res, 1 + F(idx + 1, m_left - zeros, n_left - ones))
   ```
   - Always try skipping
   - If current string fits constraints, try taking it
   - Choose the option that gives maximum count

### Complexity Analysis:

- **Time Complexity**: O(L × m × n) where L is length of strs array
  - Total possible states: `len(strs) × m × n`
  - Each state computed at most once due to memoization
  - String counting preprocessing: O(L × K) where K is average string length

- **Space Complexity**: O(L × m × n)
  - Memoization table stores up to L × m × n states
  - Additional O(L) for preprocessing counts array
  - Recursion stack depth: O(L)

### Example Walkthrough:

For `strs = ["10","0001","111001","1","0"], m = 5, n = 3`:

1. **Preprocessing**: `counts = [(1,1), (3,1), (2,4), (0,1), (1,0)]`

2. **Key Decision Points**:
   - String "111001" with (2,4): Cannot take (needs 4 ones, but n=3)
   - Optimal subset: {"10", "0001", "1", "0"}
   - Total cost: (1+3+0+1) = 5 zeros, (1+1+1+0) = 3 ones ✓
   - Result: 4 strings

### Alternative Bottom-Up DP Approach:

```python
def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    for s in strs:
        zeros, ones = s.count('0'), s.count('1')
        # Iterate backwards to avoid using updated values
        for i in range(m, zeros - 1, -1):
            for j in range(n, ones - 1, -1):
                dp[i][j] = max(dp[i][j], dp[i - zeros][j - ones] + 1)
    
    return dp[m][n]
```

This reduces space to O(m × n) but has the same time complexity.

# Tags

- Dynamic Programming
- Memoization
- 3D DP
- Knapsack Problem
- Constraint Satisfaction
- Recursion
- Subset Selection

