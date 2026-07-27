## Problem

https://leetcode.com/problems/queens-that-can-attack-the-king/description/

On a **0-indexed** `8 x 8` chessboard, there can be multiple black queens and one white king.

You are given a 2D integer array `queens` where `queens[i] = [xQueeni, yQueeni]` represents the position of the `ith` black queen on the chessboard. You are also given an integer array `king` of length `2` where `king = [xKing, yKing]` represents the position of the white king.

Return the coordinates of the black queens that can **directly attack** the king. A queen can directly attack the king if there is no other queen between them on the same row, column, or diagonal.

---

## Observations

- A queen can attack the king from 8 directions: up, down, left, right, and the 4 diagonals.
- For each direction, only the **closest** queen to the king matters — any queen behind it is blocked.
- The board is fixed at `8 x 8`, so the search space per direction is at most 7 steps.
- Instead of checking each queen's line-of-sight to the king, it is more natural to **search outward from the king** in all 8 directions and stop at the first queen encountered.
- Using a hash set for queen positions gives O(1) lookup per step.

---

## Solution

```python
class Solution:
    def queensAttacktheKing(self, queens: List[List[int]], king: List[int]) -> List[List[int]]:
        res = []
        directions = [
            (-1, 0), (1, 0), (0, -1), (0, 1),
            (-1, -1), (-1, 1), (1, -1), (1, 1)
        ]
        s_queen = set()
        for x, y in queens:
            s_queen.add((x, y))

        for dx, dy in directions:
            x, y = king
            while x >= 0 and x < 8 and y >= 0 and y < 8:
                x += dx
                y += dy
                if (x, y) in s_queen:
                    res.append([x, y])
                    break
        
        return res
```

**Step-by-step explanation:**

1. **Build a set of queen positions** — convert `queens` into a hash set `s_queen` so that position lookups are O(1).

2. **Define 8 directions** — the 8 `(dx, dy)` pairs represent all possible attack lines from the king: horizontal, vertical, and diagonal.

3. **Scan outward from the king in each direction** — for each direction, start at the king's position and advance one step at a time while staying on the board.

4. **Stop at the first queen found** — as soon as a queen is encountered in a given direction, add it to the result and `break` out of that direction's loop. Any queen further away in the same direction is blocked and irrelevant.

5. **Return the result** — after all 8 directions are checked, `res` contains exactly the queens that can directly attack the king.

**Complexity:**
- Time: O(1) — at most 8 directions × 7 steps = 56 iterations, plus O(Q) to build the set where Q ≤ 63.
- Space: O(Q) for the hash set.
