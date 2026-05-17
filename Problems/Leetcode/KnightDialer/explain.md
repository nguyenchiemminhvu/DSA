## Problem

https://leetcode.com/problems/knight-dialer/description

A chess knight on a phone pad moves in an L-shape: two squares in one direction and one square perpendicular. The phone pad layout is:
```
1 2 3
4 5 6
7 8 9
* 0 #
```

The knight can only land on numeric cells (0-9), not on `*` or `#`.

**Given** an integer `n`, return the count of distinct phone numbers of length `n` that can be dialed by:
1. Placing the knight on any numeric cell initially
2. Performing exactly `n - 1` valid knight jumps
3. Each jump must land on a numeric cell

Return the answer modulo $10^9 + 7$.

**Examples:**
- `n = 1` → Output: `10` (any starting cell)
- `n = 2` → Output: `20` (valid pairs: 04, 06, 16, 18, 27, 29, 34, 38, 40, 43, 49, 60, 61, 67, 72, 76, 81, 83, 92, 94)
- `n = 3131` → Output: `136006598`

**Constraints:** $1 \leq n \leq 5000$

## Observations

### 1. **Knight Move Geometry**
The knight moves in exactly 8 possible L-shaped directions from any position:
- 2 squares vertically, 1 square horizontally: 4 moves
- 1 square vertically, 2 squares horizontally: 4 moves

Direction vectors: `(-2,-1), (-2,1), (-1,-2), (-1,2), (1,-2), (1,2), (2,-1), (2,1)`

### 2. **Grid Structure & Boundaries**
- Grid dimensions: 4 rows × 3 columns (0-indexed)
- Valid cells: 0-9 (all numeric positions)
- Invalid cells: `*` at (3,0) and `#` at (3,2)
- Many knight moves from edge cells go out of bounds

### 3. **Connectivity Graph**
Each numeric cell connects to a limited subset of cells via valid knight moves:
- **0** → {4, 6}
- **1** → {6, 8}
- **2** → {7, 9}
- **3** → {4, 8}
- **4** → {0, 3, 9}
- **5** → {} (isolated—no valid knight moves!)
- **6** → {0, 1, 7}
- **7** → {2, 6}
- **8** → {1, 3}
- **9** → {2, 4}

The fact that **5 is unreachable** is critical: any path through 5 ends.

### 4. **Counting Principle: Path Enumeration**
This is a **path counting problem** on a directed graph where:
- We count all paths of length exactly `n` starting from any numeric cell
- Each step (transition) represents dialing one digit
- Total count = sum of all valid n-step paths

### 5. **Dynamic Programming Structure**
Define: `dp[i][j]` = number of distinct phone numbers of current length ending at cell `(i, j)`

- **Base:** Length 1: `dp[i][j] = 1` for all valid cells (10 possible starting positions)
- **Transition:** For length `len`, accumulate counts from cells that can reach `(i, j)` via knight move
- **Answer:** Sum of all `dp[i][j]` after `n - 1` transitions

### 6. **Backward Transition Efficiency**
Instead of "where can I go next," think "where did I come from":
- For cell `(nr, nc)` at step `k`, it receives contributions from all cells `(r, c)` that can reach it
- This makes the transition clean: $\text{next\_dp}[nr][nc] += \text{dp}[r][c]$

### 7. **Modulo Arithmetic**
With $n$ up to 5000, the answer grows exponentially. Modulo $10^9 + 7$ prevents overflow:
- Apply modulo during accumulation, not just at the end
- Works because $(a + b) \mod m = ((a \mod m) + (b \mod m)) \mod m$

---

## Solution

### Approach: Bottom-Up Dynamic Programming

**Intuition:** Count how many ways to reach each cell at each step.

**Algorithm:**
1. Initialize `dp[i][j] = 1` for all valid numeric cells
2. For each step from 1 to `n - 1`:
   - Create a new DP table
   - For each source cell `(r, c)` with count `dp[r][c]`:
     - For each of 8 knight move directions:
       - If target cell `(nr, nc)` is valid, add `dp[r][c]` to `next_dp[nr][nc]`
   - Update `dp = next_dp`
3. Return sum of all `dp[i][j]` values

**Key Code Section:**
```python
for steps in range(1, k):
    next_dp = [[0] * n for _ in range(m)]
    for r in range(m):
        for c in range(n):
            if grid[r][c] != -1:  # Valid source cell
                for d in range(8):
                    nr = r + dir_r[d]
                    nc = c + dir_c[d]
                    if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] != -1:
                        next_dp[nr][nc] += dp[r][c]
                        next_dp[nr][nc] %= mod
    dp = next_dp
```

### Detailed Walkthrough for `n = 2`

**Initialization:**
```
dp (length 1):
  1 1 1    (cells: 1, 2, 3)
  1 1 1    (cells: 4, 5, 6)
  1 1 1    (cells: 7, 8, 9)
  0 1 0    (cells: *, 0, #)
Total: 10
```

**Step 1 (Calculating length 2):**
For each cell, count which cells can reach it:
- Cell (0,0)=1: Reachable from {(1,2)=6, (2,1)=8} → `next_dp[0][0] = 1 + 1 = 2`
  - 6→1: 6 at (1,2) moves (-2,-1) → lands at (0,0) ✓
  - 8→1: 8 at (2,1) moves (-2,-1) → lands at (0,0) ✓
- Cell (0,1)=2: Reachable from {(2,0)=7, (2,2)=9} → `next_dp[0][1] = 1 + 1 = 2`
- Cell (0,2)=3: Reachable from {(1,0)=4, (2,1)=8} → `next_dp[0][2] = 1 + 1 = 2`
- Cell (1,0)=4: Reachable from {(0,2)=3, (2,2)=9, (3,1)=0} → `next_dp[1][0] = 1 + 1 + 1 = 3`
- ... (continue for all cells)

**Result:** `next_dp` sum = 20 ✓

### Complete Python Solution

```python
class Solution:
    def knightDialer(self, k: int) -> int:
        mod = 10**9 + 7

        # Grid: 4 rows, 3 cols; -1 marks invalid cells
        grid = [[0 for j in range(3)] for i in range(4)]
        grid[3][0] = grid[3][2] = -1  # * and #

        m, n = 4, 3
        # 8 knight move directions
        dir_r = [-2, -2, 2, 2, -1, 1, -1, 1]
        dir_c = [-1, 1, -1, 1, -2, -2, 2, 2]

        # DP[i][j] = ways to dial numbers ending at (i,j)
        dp = [[1] * n for _ in range(m)]
        dp[3][0] = dp[3][2] = 0  # Can't start at invalid cells

        # For each additional digit (steps 2 through k)
        for steps in range(1, k):
            next_dp = [[0] * n for _ in range(m)]
            
            # For each current cell
            for r in range(m):
                for c in range(n):
                    if grid[r][c] != -1:  # Valid source
                        # Try all 8 knight moves
                        for d in range(8):
                            nr = r + dir_r[d]
                            nc = c + dir_c[d]
                            
                            # Check if target is valid and in bounds
                            if 0 <= nr < m and 0 <= nc < n:
                                if grid[nr][nc] != -1:
                                    # Add ways from current cell to target
                                    next_dp[nr][nc] = (next_dp[nr][nc] + dp[r][c]) % mod
            
            dp = next_dp

        # Sum all ways for length k
        res = 0
        for i in range(m):
            for j in range(n):
                res = (res + dp[i][j]) % mod
        
        return res
```

### Complexity Analysis

| Aspect | Value |
|--------|-------|
| **Time** | $O(n)$ — n iterations, each processing 10 cells × 8 moves |
| **Space** | $O(1)$ — two fixed-size (4×3) DP tables |
| **Modulo Ops** | Applied during accumulation to prevent overflow |

### Why This Works

1. **Correctness:** We count all valid paths exactly once by building bottom-up
2. **Efficiency:** Only 10 numeric cells, so linear in the number of steps
3. **Isolation Handling:** Cell 5 naturally has 0 outgoing moves; unreachable sequences are never counted
4. **Modulo Safety:** All operations respect modular arithmetic properties

# Tags

