## Problem

https://leetcode.com/problems/reach-a-number/description/

You are standing at position `0` on an infinite number line. There is a destination at position `target`.

On the `i`-th move (1-indexed), you take exactly `i` steps either left or right.

Return the **minimum number of moves** to reach `target`.

**Constraints:** `-10^9 <= target <= 10^9`, `target != 0`

---

## Observations

**1. Symmetry.**
The problem is symmetric around 0. Going left to `-target` takes the same number of moves as going right to `+target`. So we can work with `abs(target)` and only consider positive targets.

**2. The "all-right" sum.**
If we make `n` moves all going right, the total displacement is:
$$S(n) = 1 + 2 + \cdots + n = \frac{n(n+1)}{2}$$

**3. Flipping a move.**
If instead of going right on move `i` we go left, the displacement changes by $-2i$ (we lose `+i` and gain `-i`). So every flip reduces the total by an **even** number.

**4. Reachability condition.**
To reach `target` in exactly `n` moves, we need:
- $S(n) \geq target$ (enough total distance)
- $(S(n) - target)$ is **even** (because we can only reduce $S(n)$ by even amounts via flips)

If both conditions hold, we can flip the single move $i = (S(n) - target) / 2$ to land exactly on `target`.

**5. Finding the minimum n.**
- Increment `n` until $S(n) \geq target$.
- If $S(n) = target$: done.
- If $(S(n) - target)$ is odd: add one more move. Adding move $n+1$ changes the parity of the difference by $(n+1) \mod 2$. In the worst case we need **2 extra moves** to make the difference even.

---

## Solution

```python
class Solution:
    def reachNumber(self, target: int) -> int:
        target = abs(target)   # symmetry: only consider positive side
        s = 0
        i = 1

        # Step 1: find minimum n such that S(n) >= target
        while s < target:
            s += i
            i += 1

        # s == S(i-1), and i is now (last move used + 1)
        if s == target:
            return i - 1       # exact hit, no flipping needed

        # Step 2: keep adding moves until (s - target) is even
        # Each extra move changes the parity of (s - target) by the move size mod 2
        # At most 2 extra moves are ever needed
        while (s - target) & 1:   # while difference is odd
            s += i
            i += 1

        return i - 1
```

**Walk-through — Example 1 (`target = 2`):**
| Move | s | s - target | (s-target) even? |
|------|---|------------|-----------------|
| 1    | 1 | —          | s < target      |
| 2    | 3 | 1          | No (odd)        |
| 3    | 6 | 4          | Yes → flip move 2 (size 2): 1 - 2 + 3 = 2 ✓ |

Returns **3**.

**Walk-through — Example 2 (`target = 3`):**
| Move | s | s - target | (s-target) even? |
|------|---|------------|-----------------|
| 1    | 1 | —          | s < target      |
| 2    | 3 | 0          | Yes (exact hit) |

Returns **2**.

**Time complexity:** $O(\sqrt{target})$ — we reach $S(n) \approx target$ in about $\sqrt{2 \cdot target}$ moves, and add at most 2 more.  
**Space complexity:** $O(1)$

---

# Tags

`Math` `Greedy`

