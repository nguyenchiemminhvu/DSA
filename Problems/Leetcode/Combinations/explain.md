## Problem

https://leetcode.com/problems/combinations/description/

```
Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].

You may return the answer in any order.

Example 1:

Input: n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
Explanation: There are 4 choose 2 = 6 total combinations.
Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.

Example 2:

Input: n = 1, k = 1
Output: [[1]]
Explanation: There is 1 choose 1 = 1 total combination.

Constraints:

1 <= n <= 20
1 <= k <= n
```

## Observations

1. **Combinatorial Problem**: We need to find all possible ways to choose k numbers from the range [1, n] where order doesn't matter.

2. **Mathematical Insight**: The total number of combinations is C(n,k) = n!/(k!(n-k)!). For n=4, k=2: C(4,2) = 6.

3. **Backtracking Approach**: This is a classic backtracking problem where we:
   - Build combinations incrementally
   - Make choices at each step
   - Backtrack when we reach a complete combination or exhaust possibilities

4. **Key Constraints**:
   - We need exactly k numbers in each combination
   - Numbers must be in ascending order to avoid duplicates (since [1,2] and [2,1] are the same)
   - Each number can only be used once per combination

5. **State Management**: We need to track:
   - Current position in the combination (depth)
   - Starting point for the next number to maintain order
   - Current combination being built

## Solution

The solution uses **Depth-First Search (DFS) with backtracking**:

### Algorithm Breakdown:

1. **Base Case**: When `i > k`, we have selected k numbers, so we add the current combination to results.

2. **Recursive Case**: For each valid number from `start` to `n`:
   - Add the number to current combination (`temp.append(val)`)
   - Recursively explore with next position (`i + 1`) and next starting point (`val + 1`)
   - Remove the number to backtrack (`temp.pop()`)

3. **Parameters**:
   - `i`: Current depth/position (1-indexed, represents which number we're selecting)
   - `start`: Starting point for current level to maintain ascending order

### Time & Space Complexity:

- **Time Complexity**: O(C(n,k) × k) where C(n,k) is the number of combinations and k is the cost to copy each combination
- **Space Complexity**: O(k) for the recursion stack and temporary array (excluding output space)

### Example Trace (n=4, k=2):

```
dfs(1, 1): Try numbers 1,2,3,4
  ├─ Choose 1: dfs(2, 2)
  │   ├─ Choose 2: dfs(3, 3) → i>k, add [1,2]
  │   ├─ Choose 3: dfs(3, 4) → i>k, add [1,3]  
  │   └─ Choose 4: dfs(3, 5) → i>k, add [1,4]
  ├─ Choose 2: dfs(2, 3)
  │   ├─ Choose 3: dfs(3, 4) → i>k, add [2,3]
  │   └─ Choose 4: dfs(3, 5) → i>k, add [2,4]
  └─ Choose 3: dfs(2, 4)
      └─ Choose 4: dfs(3, 5) → i>k, add [3,4]
```

Result: `[[1,2], [1,3], [1,4], [2,3], [2,4], [3,4]]`

## Tags

array, backtracking