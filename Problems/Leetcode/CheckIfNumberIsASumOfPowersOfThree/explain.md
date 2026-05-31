## Problem

https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/description/

Given an integer `n`, return `true` if it is possible to represent `n` as the sum of **distinct** powers of three. Otherwise, return `false`.

An integer `y` is a power of three if there exists an integer `x` such that `y == 3^x`.

### Examples

**Example 1:**
- Input: `n = 12`
- Output: `true`
- Explanation: `12 = 3^1 + 3^2`

**Example 2:**
- Input: `n = 91`
- Output: `true`
- Explanation: `91 = 3^0 + 3^2 + 3^4`

**Example 3:**
- Input: `n = 21`
- Output: `false`

### Constraints

- `1 <= n <= 10^7`

## Observations

1. **Distinct powers only**: Each power of three can be used **at most once**. This is the 0/1 knapsack variant, not unbounded — each "coin" (power of three) is either taken or not.

2. **Finite candidate set**: Powers of three grow exponentially, so there are at most $\lfloor \log_3 n \rfloor + 1 \approx 15$ powers of three up to $10^7$. The candidate coins array is small.

3. **Subset-sum framing**: The question reduces to: given a set of distinct powers of three, can we choose a subset that sums to exactly `n`? This is the classic 0/1 subset-sum problem.

4. **Recursive structure**: Let `F(i, s)` = "can we form sum `s` using powers from index `0` to `i-1`?" At each step we either skip the current power or include it (if it does not exceed `s`).

5. **Base cases**:
   - `s == 0`: sum achieved → `True`
   - `i == 0` and `s != 0`: no coins left, sum not achieved → `False`

6. **Greedy insight (alternative O(log n) solution)**: Writing `n` in base-3 is equivalent to checking whether every digit is 0 or 1. If any digit is 2, we would need the same power twice, which is not allowed. So `n` is representable iff its base-3 representation contains only digits 0 and 1.

## Solution

The solution presents two equivalent DP approaches (recursive top-down and iterative bottom-up) built on the 0/1 knapsack template.

### Approach 1: Top-Down Recursion (Active Solution)

```python
class Solution:
    def checkPowersOfThree(self, n: int) -> bool:
        coins = []
        candidate = 1
        while candidate <= n:
            coins.append(candidate)
            candidate *= 3

        m = len(coins)

        def F(i: int, s: int) -> bool:
            if s == 0:
                return True
            if i <= 0 and s != 0:
                return False
            res = F(i - 1, s)               # skip coins[i-1]
            if coins[i - 1] <= s:
                res = res or F(i - 1, s - coins[i - 1])  # take coins[i-1]
            return res

        return F(m, n)
```

**How it works:**

- `coins` collects all powers of three up to `n` (e.g., for `n = 12`: `[1, 3, 9]`).
- `F(i, s)` asks: *can we form sum `s` using a subset of `coins[0..i-1]`?*
- At each call we branch into two choices:
  - **Skip**: `F(i-1, s)` — don't use `coins[i-1]`.
  - **Take**: `F(i-1, s - coins[i-1])` — use `coins[i-1]`, reducing the remaining sum.
- Early termination: the `or` short-circuits as soon as a `True` branch is found.

**Complexity:**
- Time: O(2^m) in the worst case without memoization, where m ≈ 15. Acceptable given the tiny `m`, but can be memoized to O(m × n).
- Space: O(m) recursion depth.

### Approach 2: Bottom-Up DP (Commented Out)

```python
dp = [[False] * (n + 1) for _ in range(m + 1)]
for i in range(m + 1):
    dp[i][0] = True
for i in range(1, m + 1):
    for s in range(1, n + 1):
        dp[i][s] = dp[i - 1][s]                          # skip coins[i-1]
        if coins[i - 1] <= s:
            dp[i][s] = dp[i][s] or dp[i - 1][s - coins[i - 1]]  # take coins[i-1]
return dp[m][n]
```

**How it works:**

1. **Table definition**: `dp[i][s]` = `True` if sum `s` can be formed from the first `i` powers of three.
2. **Base case**: `dp[i][0] = True` for all `i` — a sum of 0 is always achievable (take nothing).
3. **Transition**: For each coin index `i` and each target sum `s`:
   - We can always skip `coins[i-1]`, inheriting `dp[i-1][s]`.
   - If `coins[i-1] <= s`, we can also try taking it: `dp[i-1][s - coins[i-1]]`.
4. **Answer**: `dp[m][n]`.

**Example Walkthrough** (`n = 12`, coins = `[1, 3, 9]`):

```
          s=0   s=1  s=2  s=3  s=4 ... s=9 ... s=12
dp[0][]    T     F    F    F    F        F        F
dp[1][]    T     T    F    F    F        F        F    (coin=1)
dp[2][]    T     T    F    T    T        F        T    (coin=3, 1+3=4, 3+3=not allowed—distinct!)
dp[3][]    T     T    F    T    T        T    ... T    (coin=9, 9+3=12 ✓)
```

**Complexity:**
- Time: O(m × n) where m ≈ 15
- Space: O(m × n); reducible to O(n) with a 1-D rolling array.

### Alternative O(log n) Solution: Base-3 Check

```python
while n > 0:
    if n % 3 == 2:
        return False
    n //= 3
return True
```

Each step examines one base-3 digit. If any digit equals 2 (meaning a power is needed twice), return `False`. This is the most efficient approach.

# Tags

#dynamic-programming #knapsack-0-1 #subset-sum #math #base-conversion
