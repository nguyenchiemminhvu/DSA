## Problem

https://leetcode.com/problems/perfect-squares/

```
Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.

Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

Constraints:

1 <= n <= 104
```

## Observations

1. **Problem Pattern**: This is essentially a variant of the coin change problem where the "`coins`" are perfect squares `(1², 2², 3², ...)`.

2. **Optimal Substructure**: To find the minimum number of perfect squares that sum to `n`, we need to consider all possible perfect squares less than or equal to `n` and recursively solve for the remaining amount.

3. **Overlapping Subproblems**: The same subproblems (finding minimum squares for smaller numbers) are computed multiple times, making this a perfect candidate for memoization/dynamic programming.

4. **BFS Limitation**: While `BFS` can solve this problem by treating it as finding the shortest path in a graph (where each node represents a number and edges represent subtracting a perfect square), it's time-limited for larger inputs due to the extensive exploration of states.

5. **Mathematical Insight**: According to Lagrange's four-square theorem, every positive integer can be represented as the sum of at most four perfect squares. However, we want the minimum number.

## Solution

The solution uses **memoized recursion (top-down dynamic programming)** similar to the coin change problem:

**Key Points:**

1. **Recurrence Relation**: `F(n) = min(F(n - j²) + 1)` for all `j` where `j² ≤ n`
   - We try subtracting each possible perfect square and add 1 to the result
   - Take the minimum among all possibilities

2. **Memoization**: Store computed results in `self.memo` to avoid recomputation

3. **Time Complexity**: `O(n × √n)` - for each number up to n, we check all perfect squares up to √n

4. **Space Complexity**: `O(n)` - for the memoization table and recursion stack

**Why DP over BFS?**
- `BFS` explores all possible combinations level by level, leading to exponential time complexity for larger inputs
- `DP` with memoization ensures each subproblem is solved only once, making it much more efficient
- The recursive structure naturally captures the optimal substructure of the problem

## Tags

math, bfs, dynamic programming