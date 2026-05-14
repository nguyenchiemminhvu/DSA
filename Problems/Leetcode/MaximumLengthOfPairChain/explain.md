# Maximum Length of Pair Chain

## Problem

https://leetcode.com/problems/maximum-length-of-pair-chain/description

You are given an array of `n` pairs `pairs` where `pairs[i] = [left_i, right_i]` and `left_i < right_i`.

A pair `p2 = [c, d]` **follows** a pair `p1 = [a, b]` if `b < c`. A chain of pairs can be formed in this fashion.

**Return the length of the longest chain which can be formed.**

You do not need to use up all the given pairs. You can select pairs in any order.

### Examples

**Example 1:**
```
Input: pairs = [[1,2],[2,3],[3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4].
```

**Example 2:**
```
Input: pairs = [[1,2],[7,8],[4,5]]
Output: 3
Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].
```

### Constraints
- `n == pairs.length`
- `1 <= n <= 1000`
- `-1000 <= left_i < right_i <= 1000`

---

## Observations

1. **Strict Inequality Constraint**: Two pairs can be chained if `b < c` (strictly less than), not `b <= c`. This means the end of the first pair must be strictly before the start of the second pair.

2. **Order Dependency**: The order in which we consider pairs significantly impacts the result. Sorting helps us process pairs in an optimal manner. Sorting by the end value (second element) is particularly useful because it naturally arranges pairs that can form longer chains.

3. **Recurrence Structure**: For each pair at position `i`, we have exactly two choices:
   - **Skip this pair**: Take the longest chain from the remaining pairs after `i` → `dp[i+1]`
   - **Take this pair**: Include this pair and find the longest chain from pairs that don't overlap with it → `1 + dp[j]` where `j` is the first pair whose start value is strictly greater than the current pair's end value

4. **Optimal Substructure**: The longest chain starting from position `i` depends only on the optimal solutions of subproblems starting from positions after `i`. This enables dynamic programming.

5. **Overlapping Subproblems**: Multiple paths through the recursion tree will require computing the same subproblems (e.g., the longest chain from position `j`). Memoization or tabulation eliminates redundant calculations.

6. **Non-Overlapping Interval Selection**: This problem is similar to the interval scheduling problem, where we want to select the maximum number of non-overlapping intervals.

---

## Solution Explanation

### Approach: Dynamic Programming (Bottom-Up Tabulation)

**Key Idea**: Build a DP table where `dp[i]` represents the longest chain we can form starting from pair `i` onwards.

**Algorithm**:
1. **Sort** pairs by their start and end values (lexicographically)
2. **Initialize** `dp` array of size `n+1`, where `dp[n] = 0` (base case: no pairs left)
3. **Iterate backwards** from index `n-1` to `0`:
   - For pair at index `i`:
     - **Option 1** (skip): `op1 = dp[i+1]`
     - **Option 2** (take): Find the first pair `j > i` where `pairs[j][0] > pairs[i][1]`, then `op2 = 1 + dp[j]`
     - **Decide**: `dp[i] = max(op1, op2)`
4. **Return** `dp[0]` (longest chain starting from the first pair)

**Time Complexity**: $O(n^2)$
- Sorting: $O(n \log n)$
- DP: $O(n^2)$ in worst case (nested loops: outer loop over `n` pairs, inner `while` loop up to `n`)

**Space Complexity**: $O(n)$
- DP array of size `n+1`

**Code**:
```python
class Solution:
    def findLongestChain(self, pairs: List[List[int]]) -> int:
        pairs.sort(key=lambda x: (x[0], x[1]))
        n = len(pairs)

        # dp[i] = longest chain starting from index i
        dp = [0] * (n + 1)
        
        # Process pairs in reverse order
        for i in range(n - 1, -1, -1):
            # Option 1: Skip current pair
            op1 = dp[i + 1]
            
            # Option 2: Take current pair and find next non-overlapping pair
            j = i + 1
            while j < n and pairs[j][0] <= pairs[i][1]:
                j += 1
            op2 = 1 + dp[j]
            
            # Take maximum
            dp[i] = max(op1, op2)
        
        return dp[0]
```

---

### Alternative Approach: Top-Down Memoization (Recursion + Caching)

**Key Idea**: Use recursion to explore both choices (skip or take) and cache results to avoid recomputation.

```python
class Solution:
    def findLongestChain(self, pairs: List[List[int]]) -> int:
        pairs.sort(key=lambda x: (x[0], x[1]))
        n = len(pairs)
        mem = {}
        
        def F(i: int) -> int:
            if i >= n:
                return 0
            if i in mem:
                return mem[i]
            
            # Option 1: Skip current pair
            op1 = F(i + 1)
            
            # Option 2: Take current pair
            j = i + 1
            while j < n and pairs[j][0] <= pairs[i][1]:
                j += 1
            op2 = 1 + F(j)
            
            res = max(op1, op2)
            mem[i] = res
            return res
        
        return F(0)
```

---

### Walkthrough: Example 1

```
pairs = [[1,2],[2,3],[3,4]]
After sorting: [[1,2],[2,3],[3,4]]

DP Table Construction (backward):

i=2: pair=[3,4]
  op1 = dp[3] = 0                    (skip, no more pairs)
  j = 3 (no pair with start > 4)     
  op2 = 1 + dp[3] = 1 + 0 = 1        (take [3,4])
  dp[2] = max(0, 1) = 1

i=1: pair=[2,3]
  op1 = dp[2] = 1                    (skip, use best from pairs[2:])
  j = 2 (pairs[2][0]=3, but 3 <= 3)  (continue)
  j = 3 (out of bounds, stop)
  op2 = 1 + dp[3] = 1 + 0 = 1        (take [2,3], nothing after it)
  dp[1] = max(1, 1) = 1

i=0: pair=[1,2]
  op1 = dp[1] = 1                    (skip, use best from pairs[1:])
  j = 1 (pairs[1][0]=2, but 2 <= 2)  (continue, overlap!)
  j = 2 (pairs[2][0]=3, and 3 > 2)   (stop, no overlap)
  op2 = 1 + dp[2] = 1 + 1 = 2        (take [1,2], then chain [3,4])
  dp[0] = max(1, 2) = 2

Final Answer: dp[0] = 2
Optimal Chain: [1,2] -> [3,4]
```

**Why is [2,3] skipped?**
- At `i=0`, we need `pairs[i][1] < pairs[j][0]`, i.e., `2 < pairs[j][0]`
- `[2,3]` has start=2, and `2 < 2` is false, so it overlaps
- `[3,4]` has start=3, and `2 < 3` is true, so it doesn't overlap ✓

---

### Walkthrough: Example 2

```
pairs = [[1,2],[7,8],[4,5]]
After sorting: [[1,2],[4,5],[7,8]]

DP Table Construction (backward):

i=2: pair=[7,8]
  op1 = dp[3] = 0
  j = 3 (no pair after [7,8])
  op2 = 1 + dp[3] = 1
  dp[2] = 1

i=1: pair=[4,5]
  op1 = dp[2] = 1
  j = 2 (pairs[2][0]=7, and 7 > 5)   (stop, no overlap)
  op2 = 1 + dp[2] = 1 + 1 = 2
  dp[1] = max(1, 2) = 2

i=0: pair=[1,2]
  op1 = dp[1] = 2
  j = 1 (pairs[1][0]=4, and 4 > 2)   (stop, no overlap)
  op2 = 1 + dp[1] = 1 + 2 = 3
  dp[0] = max(2, 3) = 3

Final Answer: dp[0] = 3
Optimal Chain: [1,2] -> [4,5] -> [7,8]
```

---

## Key Insights

1. **Sorting is crucial**: Sorting pairs lexicographically allows us to use the "next non-overlapping" logic efficiently.

2. **The choice between skip and take**: At each step, skipping is sometimes better than taking (e.g., if a larger pair blocks multiple chains). The DP correctly evaluates both.

3. **Index `j` represents the first valid next pair**: After finding `j`, we know all pairs from `i+1` to `j-1` overlap with pair `i`, and pair `j` onwards don't overlap.

4. **Why bottom-up DP?**: Processing from right to left ensures that when computing `dp[i]`, we've already computed `dp[i+1]` and `dp[j]`.

---

## Tags

- **Algorithm**: Dynamic Programming, Greedy
- **Data Structure**: Array
- **Related Topics**: Interval Scheduling, Activity Selection

