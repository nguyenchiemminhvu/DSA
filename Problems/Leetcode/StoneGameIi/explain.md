## Problem

https://leetcode.com/problems/stone-game-ii/description/

Alice and Bob take turns (Alice first) picking stones from a row of piles. On each turn, a player may take the first `X` remaining piles where `1 <= X <= 2M`, then `M = max(M, X)`. Initially `M = 1`. Both play optimally. Return the **maximum stones Alice can get**.

**Example 1:**
```
Input:  piles = [2,7,9,4,4]
Output: 10
```
Alice takes 1 pile (2), Bob takes 2 piles (7,9), Alice takes 2 piles (4,4) → 2+4+4 = **10**.

**Example 2:**
```
Input:  piles = [1,2,3,4,5,100]
Output: 104
```

**Constraints:**
- `1 <= piles.length <= 100`
- `1 <= piles[i] <= 10^4`

---

## Ideas

### Key Observations

1. **Zero-sum game** — whatever Alice doesn't take, Bob takes, and vice versa.  
   If the total sum of all stones is `S` and Alice scores `A`, then Bob scores `S - A`.  
   Maximising Alice's score = maximising `A` = minimising Bob's score.

2. **State definition** — the game state at any point is fully described by two numbers:
   - `i` : index of the first remaining pile (left boundary).
   - `M` : current value of M.

3. **Suffix sums** — precompute `suffix_sum[i]` = sum of `piles[i..n-1]`.  
   This lets us compute "sum of piles from index i to i+x-1" in O(1) as `suffix_sum[i] - suffix_sum[i+x]`.

---

### Approach — Top-Down DP (Memoization)

Define `dp(i, M)` = **maximum stones the current player can collect** starting from pile `i` with parameter `M`.

**Base case:**
- If `i >= n` → no piles left, return `0`.
- If `i + 2*M >= n` → the current player can take all remaining piles, return `suffix_sum[i]`.

**Recurrence:**

For each choice `x` in `[1, 2M]`, the current player takes piles `i..i+x-1`.  
The opponent then plays optimally from state `(i+x, max(M, x))`.

```
dp(i, M) = max over x in [1..2M] of:
               suffix_sum[i] - dp(i + x, max(M, x))
```

The subtraction works because after the current player takes `x` piles, the opponent's
optimal score from the remaining piles is `dp(i+x, max(M,x))`, so the current player
keeps the rest of `suffix_sum[i]`.

**Answer:** `dp(0, 1)`

**Complexity:**
- States: O(n²) — `i` has n values, `M` is bounded by n.
- Transitions: O(n) per state.
- **Time: O(n³)**, **Space: O(n²)** — well within limits for n ≤ 100.

---

### Walkthrough — Example 1: `piles = [2,7,9,4,4]`

```
suffix_sum = [26, 24, 17, 8, 4, 0]

dp(0,1):  try x=1 → suffix[0] - dp(1,1) = 26 - dp(1,1)
          try x=2 → suffix[0] - dp(2,2) = 26 - dp(2,2)

dp(1,1):  try x=1 → suffix[1] - dp(2,1) = 24 - dp(2,1)
          try x=2 → suffix[1] - dp(3,2) = 24 - dp(3,2)

dp(2,2):  i+2M = 2+4=6 >= 5=n → return suffix[2] = 17

dp(3,2):  i+2M = 3+4=7 >= 5=n → return suffix[3] = 8

dp(2,1):  try x=1 → suffix[2] - dp(3,1) = 17 - dp(3,1)
          try x=2 → suffix[2] - dp(4,2) = 17 - dp(4,2)

dp(3,1):  try x=1 → suffix[3] - dp(4,1) = 8 - dp(4,1)
          try x=2 → suffix[3] - dp(5,2) = 8 - 0 = 8 → return 8

dp(4,1):  try x=1 → suffix[4] - dp(5,1) = 4 - 0 = 4
          try x=2 → i+2M=6>=5 → return suffix[4]=4 → return 4

dp(3,1) = max(8-4, 8) = max(4,8) = 8
dp(4,2)  i+2M=4+4=8>=5 → return suffix[4]=4
dp(2,1) = max(17-8, 17-4) = max(9, 13) = 13

dp(1,1) = max(24-13, 24-8) = max(11, 16) = 16

dp(0,1) = max(26-16, 26-17) = max(10, 9) = 10  ✓
```
