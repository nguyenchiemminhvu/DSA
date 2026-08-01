## Problem

https://leetcode.com/problems/predict-the-winner/description/

Two players take turns picking a number from either end of `nums`. Player 1 goes first. Both play optimally. Return `true` if Player 1's final score ≥ Player 2's final score.

---

## Observations

1. **Both players are rational.** Each player always picks the end that maximizes their own total score.

2. **Minimax structure.** From any subarray `[l, r]`, the current player wants to maximize their score, while the opponent (who moves next) also plays optimally — effectively minimizing what the current player will collect in future turns.

3. **Subproblem definition.** Define `f(l, r)` = the maximum score the *current* player (whoever's turn it is) can collect from `nums[l..r]`. Both players use the same function because the roles are symmetric — "current player vs opponent" repeats every two picks.

4. **After current player picks, opponent faces the remainder.** If the current player picks `nums[l]`, the opponent faces `[l+1, r]` and will also maximize via `f(l+1, r)`. The current player's *future* score from that subtree is the total of `[l+1, r]` minus what the opponent takes, i.e., `sum(l+1, r) - f(l+1, r)`.

   However, the solution here tracks *player 1's* score specifically (not the current player's), so the opponent's optimal play is modeled as **minimizing** player 1's future gain.

5. **Overlapping subproblems → memoization.** There are $O(n^2)$ distinct `(l, r)` pairs, each computed in $O(1)$, giving $O(n^2)$ time and space.

---

## Solution Explanation

```python
class Solution:
    def predictTheWinner(self, nums: List[int]) -> bool:
        from functools import lru_cache
        @lru_cache(None)
        def p1_try_max_score(l: int, r: int) -> int:
            if l > r:
                return 0
            if l == r:
                return nums[l]
            
            pick_left = nums[l] + min(
                p1_try_max_score(l + 2, r),
                p1_try_max_score(l + 1, r - 1)
            )

            pick_right = nums[r] + min(
                p1_try_max_score(l, r - 2),
                p1_try_max_score(l + 1, r - 1)
            )

            return max(pick_left, pick_right)
        
        p1_score = p1_try_max_score(0, len(nums) - 1)
        p2_score = sum(nums) - p1_score
        return p1_score >= p2_score
```

### `p1_try_max_score(l, r)` — Player 1's best possible score from `nums[l..r]`

This function is always called when it is **Player 1's turn** to pick from `[l, r]`. (Player 2's turn is implicit in the recursion, as shown below.)

**Base cases:**
- `l > r` → empty array, score = 0.
- `l == r` → only one element, Player 1 must take it.

**Recursive case — Player 1 picks left (`nums[l]`):**

After Player 1 takes `nums[l]`, Player 2 faces `[l+1, r]` and plays optimally. Player 2 will pick whichever end leaves Player 1 with *less*:

- If Player 2 picks `nums[l+1]` → Player 1 faces `[l+2, r]` → future score: `p1_try_max_score(l+2, r)`
- If Player 2 picks `nums[r]`   → Player 1 faces `[l+1, r-1]` → future score: `p1_try_max_score(l+1, r-1)`

Player 2 minimizes Player 1's future score, so:

$$\text{pick\_left} = \textit{nums}[l] + \min\bigl(f(l+2,\, r),\; f(l+1,\, r-1)\bigr)$$

**Recursive case — Player 1 picks right (`nums[r]`):**

After Player 1 takes `nums[r]`, Player 2 faces `[l, r-1]`:

- If Player 2 picks `nums[l]`   → Player 1 faces `[l+1, r-1]` → future score: `p1_try_max_score(l+1, r-1)`
- If Player 2 picks `nums[r-1]` → Player 1 faces `[l, r-2]`   → future score: `p1_try_max_score(l, r-2)`

$$\text{pick\_right} = \textit{nums}[r] + \min\bigl(f(l,\, r-2),\; f(l+1,\, r-1)\bigr)$$

**Player 1 maximizes:**

$$f(l, r) = \max(\text{pick\_left},\; \text{pick\_right})$$

### Final answer

Once we know `p1_score = f(0, n-1)`, Player 2's score is whatever remains:

$$\text{p2\_score} = \sum \textit{nums} - \text{p1\_score}$$

Return `p1_score >= p2_score`.

---

### Worked Example: `nums = [1, 5, 2]`

```
f(0,2): Player 1 picks 1 or 2
  pick_left  = 1 + min(f(2,2), f(1,1)) = 1 + min(2, 5) = 1 + 2 = 3
  pick_right = 2 + min(f(0,0), f(1,1)) = 2 + min(1, 5) = 2 + 1 = 3
  f(0,2) = max(3, 3) = 3
```

`p1_score = 3`, `p2_score = 8 - 3 = 5`. Player 1 loses → `false`. ✓

---

### Complexity

| | |
|---|---|
| Time  | $O(n^2)$ — $n^2$ subproblems, each $O(1)$ |
| Space | $O(n^2)$ — memoization table + recursion stack $O(n)$ |
