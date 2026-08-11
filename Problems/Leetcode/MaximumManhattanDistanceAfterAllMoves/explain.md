## Problem

https://leetcode.com/problems/maximum-manhattan-distance-after-all-moves/description/

You are given a string `moves` consisting of the characters `'U'`, `'D'`, `'L'`, `'R'`, and `'_'`.

Starting from the origin `(0, 0)`, each character represents one move on a 2D plane:
- `'U'`: Move up by 1 unit.
- `'D'`: Move down by 1 unit.
- `'L'`: Move left by 1 unit.
- `'R'`: Move right by 1 unit.
- `'_'`: Can be independently replaced with any one of `'U'`, `'D'`, `'L'`, or `'R'`.

Return the **maximum Manhattan distance** from the origin that can be achieved after all moves have been performed.

---

## Observations

1. **Manhattan distance is independent on each axis.**  
   The Manhattan distance is `|x| + |y|`. Movement along the X-axis (`L`/`R`) and Y-axis (`U`/`D`) are completely independent, so we can reason about each axis separately.

2. **Fixed moves partially determine the final position.**  
   - Net vertical displacement: `U - D` (positive = up, negative = down).
   - Net horizontal displacement: `R - L` (positive = right, negative = left).
   - The fixed moves already lock in a "bias" along each axis.

3. **Wildcards `'_'` should amplify the dominant direction.**  
   To maximize the total distance, each `'_'` should be assigned to whichever axis and direction increases the Manhattan distance the most. Since the axes are independent, every `'_'` should reinforce the already-dominant direction on one of the axes.

   More specifically, the optimal strategy is to assign **all** `'_'` moves to a single direction that is already "winning". For example:
   - If there are more `U` than `D`, assign `'_'` to `'U'`.
   - If `U == D`, assign `'_'` to either `'U'` or `'D'` — it doesn't matter which axis, just pick one and go all in.

   The key insight: it is never beneficial to split wildcards between opposing directions or between axes, because that would cancel out contributions.

4. **Each wildcard contributes exactly +1 to the total Manhattan distance.**  
   No matter what the fixed moves look like, you can always use a `'_'` to extend the net displacement in one direction by 1. Therefore, all `c['_']` wildcards contribute `c['_']` to the final answer.

---

## Solution

```python
from collections import Counter

class Solution:
    def maxDistance(self, moves: str) -> int:
        c = Counter(moves)
        return abs(c['U'] - c['D']) + abs(c['L'] - c['R']) + c['_']
```

### Explanation

- `abs(c['U'] - c['D'])`: The net vertical distance from fixed moves. Opposing moves cancel each other out.
- `abs(c['L'] - c['R'])`: The net horizontal distance from fixed moves.
- `c['_']`: All wildcards are assigned greedily to the dominant direction on the dominant axis, each contributing exactly +1.

**Time complexity:** $O(n)$ — single pass to count characters.  
**Space complexity:** $O(1)$ — only 5 possible characters to count.
