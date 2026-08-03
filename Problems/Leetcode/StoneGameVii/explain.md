## Problem

https://leetcode.com/problems/stone-game-vii/description/

Alice and Bob take turns playing a game, with **Alice starting first**.

There are `n` stones arranged in a row. On each player's turn, they can remove either the **leftmost** or **rightmost** stone from the row and receive points equal to the **sum of the remaining stones' values** in the row. The winner is the one with the higher score when there are no stones left to remove.

Bob found that he will always lose this game, so he decided to **minimize** the score difference. Alice's goal is to **maximize** the difference in the score.

Given an array of integers `stones` where `stones[i]` represents the value of the `i`-th stone from the left, return **the difference in Alice and Bob's score** if they both play optimally.

**Constraints:**
- `n == stones.length`
- `2 <= n <= 1000`
- `1 <= stones[i] <= 1000`

**Example 1:**
```
Input: stones = [5,3,1,4,2]
Output: 6
Explanation:
- Alice removes 2 → gets 5+3+1+4 = 13. Alice=13, Bob=0,  stones=[5,3,1,4]
- Bob   removes 5 → gets 3+1+4   =  8. Alice=13, Bob=8,  stones=[3,1,4]
- Alice removes 3 → gets 1+4     =  5. Alice=18, Bob=8,  stones=[1,4]
- Bob   removes 1 → gets 4       =  4. Alice=18, Bob=12, stones=[4]
- Alice removes 4 → gets 0       =  0. Alice=18, Bob=12, stones=[]
Score difference = 18 - 12 = 6
```

**Example 2:**
```
Input: stones = [7,90,5,1,100,10,10,2]
Output: 122
```

---

## Observations

1. **Turn-based game on a subarray:** At every step, the current player picks from either end of the remaining subarray `[l, r]`. After removing a stone, the player scores the sum of what's left.

2. **Zero-sum framing:** Both players play optimally but with opposite goals — Alice maximizes the score difference while Bob minimizes it. This is a classic **minimax** problem, but we can simplify it.

3. **Key insight — score difference, not individual scores:** Instead of tracking each player's absolute score, define `F(l, r)` as the **maximum score difference** the *current player* can achieve over the *opponent* within subarray `[l, r]`.

   - If the current player removes the **rightmost** stone `stones[r]`, they score `sum(l, r-1)`, and the opponent then faces subarray `[l, r-1]` and will achieve `F(l, r-1)` advantage over the current player.  
     Net difference = `sum(l, r-1) - F(l, r-1)`

   - If the current player removes the **leftmost** stone `stones[l]`, they score `sum(l+1, r)`, and the opponent then faces subarray `[l+1, r]` and will achieve `F(l+1, r)` advantage over the current player.  
     Net difference = `sum(l+1, r) - F(l+1, r)`

   - The current player picks whichever option maximizes their advantage:
     $$F(l, r) = \max\bigl(\text{sum}(l, r-1) - F(l, r-1),\; \text{sum}(l+1, r) - F(l+1, r)\bigr)$$

4. **Prefix sums** allow computing any subarray sum in O(1), turning each state evaluation into constant time.

5. **Subproblem count:** There are $O(n^2)$ subproblems `(l, r)`, each solved in $O(1)$, giving an overall **time complexity of O(n²)** with **O(n²) space** for memoization, or **O(n) space** with the bottom-up rolling array trick.

---

## Solution Explanation

### Recursive + Memoization (Top-Down)

```python
mem = {}
def F(l: int, r: int) -> int:
    if l >= r:
        return 0
    if (l, r) in mem:
        return mem[(l, r)]
    left  = (prefix_sum[r]     - prefix_sum[l])     - F(l, r - 1)  # remove rightmost
    right = (prefix_sum[r + 1] - prefix_sum[l + 1]) - F(l + 1, r)  # remove leftmost
    mem[(l, r)] = max(left, right)
    return mem[(l, r)]
return F(0, n - 1)
```

Straightforward top-down DP. `F(0, n-1)` gives Alice's score advantage over Bob.

---

### Bottom-Up DP with Space Optimization (O(n) space)

The key observation for reducing space is that when computing `F(l, r)` for a given `length`, we only need values from `length - 1`:

- `F(l, r-1)` has the same `l`, one step shorter → `dp[l]` from the previous length iteration.
- `F(l+1, r)` has `l+1`, one step shorter → `dp[l+1]` from the previous length iteration.

By iterating **left to right** over `l` within each length, and updating `dp[l]` in place, we can reuse a **1D array**:

```python
dp = [0] * n  # dp[l] = F(l, l + length - 1) for the current length being processed

for length in range(2, n + 1):
    for l in range(n - length + 1):
        r = l + length - 1
        left  = (prefix_sum[r]     - prefix_sum[l])     - dp[l]      # remove rightmost
        right = (prefix_sum[r + 1] - prefix_sum[l + 1]) - dp[l + 1]  # remove leftmost
        dp[l] = max(left, right)

return dp[0]
```

**Why does updating left-to-right work?**  
When we compute `dp[l]` for the current `length`, `dp[l+1]` has **not yet been updated** in this iteration (we haven't reached it), so it still holds the value from `length - 1`, which is exactly `F(l+1, r)` we need. Similarly, the old `dp[l]` (before overwriting) represents `F(l, r-1)`. The in-place update is safe because we only read `dp[l+1]` (future index) and immediately overwrite `dp[l]` (current index).

**Complexity:**
- **Time:** O(n²) — two nested loops.
- **Space:** O(n) — single 1D DP array plus prefix sum array.

