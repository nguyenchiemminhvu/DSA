## Problem

https://leetcode.com/problems/stone-game-iv/

Alice and Bob take turns playing a game, with Alice starting first. Initially, there are `n` stones in a pile. On each player's turn, that player removes any **non-zero perfect square** number of stones. If a player cannot make a move, they lose. Given `n`, return `true` if Alice wins assuming both players play optimally.

---

## Observations

1. **Game state = remaining stones.** The only information that matters is how many stones are left — not whose turn it is — because both players face the same choices from any given count.

2. **Win/Lose framing (Sprague-Grundy intuition).** A position is a **Losing position (L)** if every possible move leads to a Winning position for the opponent. A position is a **Winning position (W)** if at least one move leads to a Losing position for the opponent.

3. **Base case:** `remain = 0` means the current player has no move → they lose → it is a **Losing position**.

4. **Recurrence:**
   - Current player **wins** (`W`) if there exists some square `k²` such that `remain - k²` is a Losing position for the opponent.
   - Current player **loses** (`L`) if every square `k²` leads to a Winning position for the opponent.

5. **Pattern (small values):**
   | n | moves available | result |
   |---|---|---|
   | 0 | none | **L** |
   | 1 | −1→0(L) | **W** |
   | 2 | −1→1(W) | **L** |
   | 3 | −1→2(L) | **W** |
   | 4 | −1→3(W), −4→0(L) | **W** |
   | 5 | −1→4(W), −4→1(W) | **L** |
   | 6 | −1→5(L) | **W** |
   | 7 | −1→6(W), −4→3(W) | **L** |

6. **The `a_turn` parameter is redundant.** Because both players play by the same rule (remove a square, try to force the opponent into a losing spot), `F(remain)` already captures "does the *current* player* win?" without needing to track whose turn it is.

---

## Solution Explanation

The provided solution uses **top-down memoization** (recursive + `lru_cache`).

```python
class Solution:
    def winnerSquareGame(self, n: int) -> bool:
        def list_squares(n: int) -> list[int]:
            squares = []
            i = 1
            while i * i <= n:
                squares.append(i * i)
                i += 1
            return squares
        
        squares = list_squares(n)

        from functools import lru_cache
        @lru_cache(None)
        def F(remain: int, a_turn: bool) -> bool:
            if remain == 0:
                return not a_turn   # whoever faces 0 stones loses
            
            if a_turn:
                # Alice wins if ANY move puts Bob in a losing state
                for val in squares:
                    if val > remain:
                        break
                    if F(remain - val, False):
                        return True
                return False
            else:
                # Bob wins if ANY move puts Alice in a losing state
                # i.e., Alice loses if Bob can force it => return False for Alice
                for val in squares:
                    if val > remain:
                        break
                    if not F(remain - val, True):
                        return False
                return True
        
        return F(n, True)
```

**Step-by-step:**
1. Pre-compute all perfect squares `≤ n`.
2. `F(remain, a_turn)` returns `True` if Alice ultimately wins from this state.
3. At `remain = 0`, the player to move loses → Alice wins iff it is **not** Alice's turn.
4. On Alice's turn: try every valid square removal; if any leads to a state where Alice wins, return `True`.
5. On Bob's turn: Bob plays optimally against Alice; if Bob can find any move where Alice does **not** win, he takes it. Alice only wins if Bob has **no** such move.
6. `lru_cache` ensures each `(remain, turn)` state is computed only once → **O(n √n)** time.

**Simplified equivalent** (since the turn symmetry means we only need "does current player win"):

```python
@lru_cache(None)
def wins(remain: int) -> bool:
    if remain == 0:
        return False  # current player loses
    i = 1
    while i * i <= remain:
        if not wins(remain - i * i):
            return True  # found a move that puts opponent in losing state
        i += 1
    return False

return wins(n)
```

**Complexity:**
- **Time:** O(n √n) — `n` states, each iterating over O(√n) squares.
- **Space:** O(n) — memoization table.
