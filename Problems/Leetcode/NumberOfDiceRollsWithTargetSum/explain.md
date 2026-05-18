## Problem

https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/description

Given `n` dice, each with `k` faces numbered 1 to k, return the number of ways to roll all dice such that the sum of face values equals `target`. Return the result modulo $10^9 + 7$.

**Constraints:**
- $1 \leq n, k \leq 30$
- $1 \leq target \leq 1000$

**Examples:**
- `n=1, k=6, target=3` → Output: `1` (only one way: roll a 3)
- `n=2, k=6, target=7` → Output: `6` (ways: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1)
- `n=30, k=30, target=500` → Output: `222616187` (modulo $10^9 + 7$)

## Observations

### Key Insights

1. **Subproblem Structure**: This is a counting problem where we need to count combinations. We can think of it as: "How many ways can we achieve `target` sum using exactly `i` dice?" This suggests dynamic programming.

2. **Recurrence Relation**: For each die added, we can roll values 1 to k. If we've already reached some partial sum with (i-1) dice, adding die i with value v extends that to a new sum. The key observation is:
   - `ways(i, remain) = sum of ways(i-1, remain - val)` for all valid values `val` from 1 to k

3. **Base Cases**:
   - With 0 dice, we can only sum to 0 (exactly 1 way: roll nothing)
   - If at any point the remaining sum becomes negative or impossible (too large for remaining dice), there are 0 ways

4. **State Space**: We need a 2D state: `(number of dice used, remaining sum to achieve)`. The state space is $O(n \times target)$, which is manageable given constraints.

5. **Modulo Arithmetic**: Since answers can be very large, we apply modulo $10^9 + 7$ at each step to avoid overflow.

### Why DP Works Here

This is a **counting DP** problem where:
- We're counting the number of ways to achieve a goal (target sum)
- Each subproblem (fewer dice, smaller remaining sum) depends on previously solved subproblems
- No optimal choice criterion—we just need to count all possibilities

## Solution

### Approach 1: Recursive DP with Memoization (Top-Down)

```python
def F(i, remain):
    # i: number of dice remaining to roll
    # remain: remaining sum needed
    
    # Base cases
    if i == 0:
        return 1 if remain == 0 else 0  # Success only if sum is exactly 0
    if remain <= 0:
        return 0  # Impossible to achieve
    
    # Recursive case: try rolling each face value
    ways = 0
    for val in range(1, k + 1):
        ways += F(i - 1, remain - val)
    return ways
```

**How it works:**
- For each die, we try all k possible face values
- For each value, we recursively count ways to reach the target with remaining dice and reduced remaining sum
- We sum all the ways across different choices

**Time Complexity**: $O(n \times target \times k)$ with memoization (each state computed once)
**Space Complexity**: $O(n \times target)$ for memoization cache

### Approach 2: Iterative DP (Bottom-Up)

```python
MOD = 10**9 + 7
dp = [[0] * (target + 1) for _ in range(n + 1)]
dp[0][0] = 1  # Base case: 0 dice, sum 0 = 1 way

for i in range(1, n + 1):              # For each die
    for remain in range(1, target + 1): # For each possible remaining sum
        for val in range(1, k + 1):     # Try each face value
            if remain - val >= 0:        # Only if valid
                dp[i][remain] += dp[i-1][remain - val]
                dp[i][remain] %= MOD
```

**How it works:**
- `dp[i][remain]` = number of ways to get sum = `remain` using exactly `i` dice
- We fill the table iteratively, bottom-up
- For each die i and each target sum remain, we check all k possible face values
- We sum contributions from the previous die state

**Time Complexity**: $O(n \times target \times k)$
**Space Complexity**: $O(n \times target)$

### Trace Example (n=2, k=6, target=7)

| i\remain | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------|---|---|---|---|---|---|---|---|
| 0        | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1        | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 0 |
| 2        | 0 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |

- `dp[1][1] = 1`: One die rolling 1
- `dp[2][7]` sums contributions from die 1 rolling different values:
  - Roll 1: `dp[1][6] = 1` (first die shows 6)
  - Roll 2: `dp[1][5] = 1` (first die shows 5)
  - Roll 3: `dp[1][4] = 1` (first die shows 4)
  - Roll 4: `dp[1][3] = 1` (first die shows 3)
  - Roll 5: `dp[1][2] = 1` (first die shows 2)
  - Roll 6: `dp[1][1] = 1` (first die shows 1)
  - Total: 6 ways ✓

### Space Optimization

Since `dp[i][remain]` only depends on `dp[i-1][remain - val]`, we can use a 1D array:

```python
dp = [0] * (target + 1)
dp[0] = 1
for i in range(n):
    new_dp = [0] * (target + 1)
    for remain in range(target + 1):
        for val in range(1, k + 1):
            if remain - val >= 0:
                new_dp[remain] += dp[remain - val]
                new_dp[remain] %= MOD
    dp = new_dp
```

**Space Complexity**: Reduced to $O(target)$

## Complexity Analysis

| Aspect | Bottom-Up DP | Top-Down DP |
|--------|-------------|-----------|
| Time | $O(n \times target \times k)$ | $O(n \times target \times k)$ |
| Space | $O(n \times target)$ | $O(n \times target)$ |
| Cache Hit | Not applicable | High (each state computed once) |
| Implementation | Slightly more code | More intuitive recursion |

# Tags
- Dynamic Programming
- Counting/Combinatorics
- Memoization
- Modular Arithmetic

