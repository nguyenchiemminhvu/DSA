## Problem

https://leetcode.com/problems/stone-game-iii/description/

Alice and Bob take turns picking stones from a row (Alice goes first). On each turn, a player may take **1, 2, or 3** stones from the front of the remaining row. Each player's score is the sum of the values of stones they take. Both play **optimally** to maximize their own score.

Return `"Alice"` if Alice wins, `"Bob"` if Bob wins, or `"Tie"` if they end with the same score.

---

## Observations

1. **Zero-sum perspective**: The total sum of all stones is fixed. If Alice gains more than half the total, Bob gets less — and vice versa. So the key insight is: **maximizing your own score is equivalent to maximizing (your score − opponent's score)**.

2. **Recursive substructure**: At index `i`, the current player faces the same type of decision as at any other index. They pick 1, 2, or 3 stones, then the opponent faces the sub-problem starting at `i+1`, `i+2`, or `i+3`. This defines a clean recursive structure.

3. **What does the recursive function return?** Instead of tracking both players' scores separately, define `dp(i)` as the **maximum score advantage** the current player (whoever's turn it is) can achieve from index `i` onward — i.e., `(current player's score) − (opponent's score)` from position `i` to the end.

4. **Why does subtracting work?** When the current player takes stones worth `S` and then the opponent plays optimally from `i + k`, the opponent achieves a score advantage of `dp(i + k)` from their perspective. That means from the current player's perspective, the net gain is `S − dp(i + k)`. The current player maximizes over all three choices.

5. **Base case**: If `i >= n`, there are no stones left, so the score advantage is `0`.

6. **Final answer**: Call `dp(0)` for Alice. Since Alice is the "current player" at index 0:
   - `dp(0) > 0` → Alice wins
   - `dp(0) < 0` → Bob wins
   - `dp(0) == 0` → Tie

---

## Solution Explanation

```python
class Solution:
    def stoneGameIII(self, values: List[int]) -> str:
        n = len(values)
        
        from functools import lru_cache
        @lru_cache(None)
        def a_max_score(i: int) -> int:
            if i >= n:
                return 0
            
            take_1 = values[i] - a_max_score(i + 1)
            take_2 = float('-inf')
            if i + 1 < n:
                take_2 = values[i] + values[i + 1] - a_max_score(i + 2)
            take_3 = float('-inf')
            if i + 2 < n:
                take_3 = values[i] + values[i + 1] + values[i + 2] - a_max_score(i + 3)
            return max(take_1, take_2, take_3)
        
        a_score = a_max_score(0)
        if a_score == 0:
            return "Tie"
        if a_score > 0:
            return "Alice"
        return "Bob"
```

### Step-by-step walkthrough

- `a_max_score(i)` returns the **score advantage of the current player** starting from index `i`.
- At each position, the current player tries all three options (take 1, 2, or 3 stones):
  - **Take 1**: gain `values[i]`, then the opponent plays from `i+1` with advantage `a_max_score(i+1)`. Net for current player: `values[i] - a_max_score(i+1)`.
  - **Take 2**: gain `values[i] + values[i+1]`, net: `values[i] + values[i+1] - a_max_score(i+2)`.
  - **Take 3**: gain `values[i] + values[i+1] + values[i+2]`, net: `values[i] + values[i+1] + values[i+2] - a_max_score(i+3)`.
- The current player picks the option that **maximizes** their advantage.
- `lru_cache` memoizes results to avoid redundant computation.

### Complexity

| | |
|---|---|
| **Time** | $O(n)$ — each index `i` is computed once |
| **Space** | $O(n)$ — recursion stack + cache |

### Example trace: `[1, 2, 3, 7]`

- `dp(3)` = `7 - dp(4)` = `7 - 0` = `7`
- `dp(2)` = max of:
  - take 1: `3 - dp(3)` = `3 - 7` = `-4`
  - take 2 (out of bounds for index 4): `3 + 7 - dp(4)` = `10`
  - → `dp(2)` = `10`
- `dp(1)` = max of:
  - take 1: `2 - dp(2)` = `2 - 10` = `-8`
  - take 2: `2 + 3 - dp(3)` = `5 - 7` = `-2`
  - take 3: `2 + 3 + 7 - dp(4)` = `12`
  - → `dp(1)` = `12`
- `dp(0)` = max of:
  - take 1: `1 - dp(1)` = `1 - 12` = `-11`
  - take 2: `1 + 2 - dp(2)` = `3 - 10` = `-7`
  - take 3: `1 + 2 + 3 - dp(3)` = `6 - 7` = `-1`
  - → `dp(0)` = `-1` → **Bob wins** ✓
