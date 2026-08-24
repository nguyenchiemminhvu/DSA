## Problem

https://leetcode.com/problems/stone-game-viii/description

Alice and Bob take turns (Alice first). There are `n` stones in a row. On each turn, a player:
1. Chooses integer `x > 1` and removes the **leftmost x stones**.
2. Adds the sum of removed stones to their score.
3. Places a new stone with that sum value on the **left side**.

The game ends when only one stone remains. Alice wants to **maximize** `(Alice's score - Bob's score)`, Bob wants to **minimize** it. Return the optimal score difference.

---

## Key Observations

### Prefix Sum Reformulation

Let `prefix[i] = stones[0] + stones[1] + ... + stones[i]`.

When a player removes the leftmost `x` stones, they score `prefix[x-1]` and leave that value as the new leftmost stone. The critical insight:

> **The next player is forced to include this new stone** in their removal (since x > 1 always), meaning they must take at least `prefix[x-1]` plus one more stone to the right.

This means each turn effectively selects a **prefix sum index**: the current player picks some index `i` (1 ≤ i ≤ n-1), scores `prefix[i]`, and the opponent must then pick some index `j > i`.

The problem reduces to: **two players alternately pick indices from left to right (each pick must be strictly greater than the previous), and the score difference is the sum of values picked by Alice minus those by Bob.**

---

## Ideas / Approaches

### Approach: Suffix DP (Greedy from Right)

**Define:** `dp[i]` = the optimal score difference `(current player - opponent)` when the current player can choose any index from `i` to `n-1`.

**Recurrence:**
- If current player picks index `i`: they gain `prefix[i]`, then opponent plays optimally from `i+1`, giving `dp[i+1]` advantage to opponent.
  - Net for current player = `prefix[i] - dp[i+1]`
- If current player skips index `i` (picks later): result is `dp[i+1]`

So:
```
dp[i] = max(prefix[i] - dp[i+1],  dp[i+1])
```

**Base case:** `dp[n-1] = prefix[n-1]` (only one choice left)

**Answer:** `dp[1]` (Alice's first valid move is picking index 1, since x > 1 means at least 2 stones removed)

**Time Complexity:** O(n)  
**Space Complexity:** O(1) (can use a single variable scanning right to left)

#### Step-by-step on Example 1: `stones = [-1, 2, -3, 4, -5]`

| i | prefix[i] | dp[i]                           |
|---|-----------|----------------------------------|
| 4 | -3        | -3                               |
| 3 | 2         | max(2 - (-3), -3) = max(5,-3) = 5|
| 2 | -2        | max(-2 - 5, 5) = max(-7, 5) = 5  |
| 1 | 1         | max(1 - 5, 5) = max(-4, 5) = 5   |

Answer = `dp[1] = 5` ✓

#### Step-by-step on Example 2: `stones = [7,-6,5,10,5,-2,-6]`

| i | prefix[i] | dp[i]                              |
|---|-----------|-------------------------------------|
| 6 | 13        | 13                                  |
| 5 | 19        | max(19 - 13, 13) = max(6,13) = 13   |
| 4 | 21        | max(21 - 13, 13) = max(8,13) = 13   |
| 3 | 16        | max(16 - 13, 13) = max(3,13) = 13   |
| 2 | 6         | max(6 - 13, 13) = max(-7,13) = 13   |
| 1 | 1         | max(1 - 13, 13) = max(-12,13) = 13  |

Answer = `dp[1] = 13` ✓

