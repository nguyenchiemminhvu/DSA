## Problem

https://leetcode.com/problems/minimum-cost-to-split-into-ones/description/

You are given an integer `n`.

In one operation, you may split an integer `x` into two positive integers `a` and `b` such that `a + b = x`.

The cost of this operation is `a * b`.

Return an integer denoting the minimum total cost required to split the integer `n` into `n` ones.

### Examples

**Example 1:**
- Input: `n = 3`
- Output: `3`
- Explanation:
  - Split 3 into 1 and 2: cost = 1 * 2 = 2
  - Split 2 into 1 and 1: cost = 1 * 1 = 1
  - Total cost: 2 + 1 = 3

**Example 2:**
- Input: `n = 4`
- Output: `6`
- Explanation:
  - Split 4 into 2 and 2: cost = 2 * 2 = 4
  - Split 2 into 1 and 1: cost = 1 * 1 = 1
  - Split 2 into 1 and 1: cost = 1 * 1 = 1
  - Total cost: 4 + 1 + 1 = 6

### Constraints
- $1 \leq n \leq 500$

## Observations

1. **Base Case**: When `n = 1`, we already have a single 1, so no operations are needed. Cost = 0.

2. **Cost Structure**: For any split of `x` into `a` and `b`:
   - We pay cost `a * b` immediately
   - We still need to split `a` and `b` further into ones
   - The total cost is: `(a * b) + cost(a) + cost(b)`

3. **Greedy Insight (Key Observation)**:
   - If we have a number `x`, we need to split it completely into ones
   - The sum of all intermediate values we multiply is always constant
   - When we split `x` into `a` and `b`, we eventually split both down to ones
   - The cost is the sum of all products at each level
   
4. **Mathematical Pattern**:
   - For `n = 1`: cost = 0
   - For `n = 2`: 1 split (1, 1) → cost = 1 * 1 = 1
   - For `n = 3`: split (1, 2) → 1*2=2, then (1,1) → 1*1=1, total = 3
   - For `n = 4`: split (2, 2) → 2*2=4, then (1,1) → 1*1=1, (1,1) → 1*1=1, total = 6
   - For `n = 5`: optimal = split (2, 3) → 2*3=6, then (1,1)→1, (1,2)→2, (1,1)→1, total = 10
   - Pattern: 0, 1, 3, 6, 10, ... = **sum from 1 to (n-1)** = $\frac{n(n-1)}{2}$

5. **Why is balanced splitting optimal?**
   - At each level, we want to split as evenly as possible
   - This ensures smaller numbers are multiplied at deeper levels
   - The contribution of each "1" to the final cost is its depth times
   - Balanced splitting minimizes the total depth

6. **Why the formula works**:
   - Each of the (n-1) "merge operations" (from n ones back to n) contributes exactly once to the cost
   - The contribution pattern follows: when we have k ones left to create, we do operations that sum to k-1
   - Total: $(n-1) + (n-2) + (n-3) + ... + 1 = \frac{n(n-1)}{2}$

## Solution

### Approach 1: Recursive with Memoization (Bottom-Up Thinking)

```python
def minCost(self, n: int) -> int:
    mem = {}
    def F(i: int) -> int:
        if i <= 1:
            return 0
        if i in mem:
            return mem[i]
        l, r = 1, i - 1
        cost = float('inf')
        while l <= r:
            cost = min(cost, (l * r) + F(l) + F(r))
            l += 1
            r -= 1
        mem[i] = cost
        return cost
    return F(n)
```

- **Time Complexity**: $O(n^2)$ - for each number we try all splits
- **Space Complexity**: $O(n)$ - memoization cache
- **Observation**: This explores all possible split strategies

### Approach 2: Bottom-Up DP (Iterative)

```python
def minCost(self, n: int) -> int:
    dp = [float('inf') for _ in range(n + 1)]
    dp[0] = dp[1] = 0
    for i in range(2, n + 1):
        l, r = 1, i - 1
        while l <= r:
            dp[i] = min(dp[i], (l * r) + dp[l] + dp[r])
            l += 1
            r -= 1
    return dp[n]
```

- **Time Complexity**: $O(n^2)$
- **Space Complexity**: $O(n)$
- Same as approach 1 but iterative, easier to understand the DP transition

### Approach 3: Optimized DP with Symmetry

```python
def minCost(self, n: int) -> int:
    dp = [float('inf') for _ in range(n + 1)]
    dp[0] = dp[1] = 0
    for i in range(2, n + 1):
        l, r = 1, i - 1
        dp[i] = min(dp[i], (l * r) + dp[l] + dp[r])
    return dp[n]
```

- **Key Insight**: Due to symmetry, we only need to check `l = 1` and `r = i - 1`
- The optimal split is always between (1, i-1)
- **Time Complexity**: $O(n)$
- **Space Complexity**: $O(n)$

### Approach 4: Mathematical Formula (Optimal)

```python
def minCost(self, n: int) -> int:
    return n * (n - 1) // 2
```

- **Time Complexity**: $O(1)$
- **Space Complexity**: $O(1)$
- **Derivation**: The minimum cost is the sum of all integers from 1 to n-1
  - Formula: $\sum_{i=1}^{n-1} i = \frac{n(n-1)}{2}$

## Why the Formula Works

When we split optimally (greedily splitting to maximize balance):
- Split n into (1, n-1): cost = 1 * (n-1) = n-1
- Then we need to split the remaining (n-1) into ones
- This costs the same as solving the problem for (n-1), which is $\frac{(n-1)(n-2)}{2}$
- Total: $(n-1) + \frac{(n-1)(n-2)}{2} = \frac{n(n-1)}{2}$

The insight is that **the minimum cost is always to split one '1' away each time**, and the cost pattern forms the triangular number sequence.

## Verification with Examples

- **n = 1**: $\frac{1 \cdot 0}{2} = 0$ ✓
- **n = 2**: $\frac{2 \cdot 1}{2} = 1$ ✓
- **n = 3**: $\frac{3 \cdot 2}{2} = 3$ ✓
- **n = 4**: $\frac{4 \cdot 3}{2} = 6$ ✓
- **n = 5**: $\frac{5 \cdot 4}{2} = 10$ ✓

# Tags

Dynamic Programming, Memoization, Mathematical Pattern, Greedy

