## Problem

https://leetcode.com/problems/permutations/

```
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]

Example 3:

Input: nums = [1]
Output: [[1]]

Constraints:

1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
```

## Observations

1. **Problem Nature**: This is a classic backtracking problem where we need to generate all possible permutations of distinct integers.

2. **Permutation Properties**: 
   - For n distinct elements, there are n! total permutations
   - Each permutation uses every element exactly once
   - The order matters (unlike combinations)

3. **Constraints Analysis**:
   - Small input size (≤ 6 elements) makes recursive backtracking feasible
   - All integers are unique, so no need to handle duplicates
   - Maximum 6! = 720 permutations to generate

4. **Algorithm Choice**: Backtracking with DFS is ideal because:
   - We build permutations incrementally
   - We can backtrack when a path is complete
   - Natural recursive structure matches the problem

## Solution

**Approach: Backtracking with DFS**

The solution uses a depth-first search with backtracking to generate all permutations:

### Key Components:

1. **State Tracking**:
   - `temp[]`: Current permutation being built
   - `s`: Set to track which numbers are already used
   - `res[]`: Final result storing all permutations

2. **Recursive Function `dfs(i)`**:
   - Parameter `i`: Current position in the permutation (0 to n-1)
   - Base case: When `i == n`, we have a complete permutation

3. **Backtracking Process**:
   ```
   For each unused number:
   1. Add number to current permutation (temp)
   2. Mark as used (add to set s)
   3. Recursively build rest of permutation
   4. Backtrack: remove from temp and set
   ```

### Algorithm Flow:

```
dfs(0) - Start building permutation
├── Try nums[0] if not used
│   ├── Add to temp, mark used
│   ├── dfs(1) - Build position 1
│   └── Backtrack: remove from temp and set
├── Try nums[1] if not used
│   ├── Add to temp, mark used  
│   ├── dfs(1) - Build position 1
│   └── Backtrack: remove from temp and set
└── ... continue for all numbers
```

### Time & Space Complexity:

- **Time**: O(n! × n) 
  - n! permutations to generate
  - O(n) to copy each permutation to result
- **Space**: O(n) 
  - Recursion depth: O(n)
  - Auxiliary space for temp array and set: O(n)

### Example Trace for [1,2,3]:

```
dfs(0): try 1 → temp=[1], s={1}
  dfs(1): try 2 → temp=[1,2], s={1,2}  
    dfs(2): try 3 → temp=[1,2,3], s={1,2,3}
      dfs(3): i==n → add [1,2,3] to result
    backtrack: temp=[1,2], s={1,2}
  backtrack: temp=[1], s={1}
  dfs(1): try 3 → temp=[1,3], s={1,3}
    dfs(2): try 2 → temp=[1,3,2], s={1,2,3}
      dfs(3): i==n → add [1,3,2] to result
    ... continue pattern
```

**Note**: The `nums.sort()` at the beginning ensures deterministic output order, though it's not required for correctness since the problem allows any order.

## Tags

array, backtracking