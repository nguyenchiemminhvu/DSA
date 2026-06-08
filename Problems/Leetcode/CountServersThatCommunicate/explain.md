## Problem

https://leetcode.com/problems/count-servers-that-communicate/description/

You are given a map of a server center represented as an `m × n` integer matrix `grid`, where `1` means there is a server on that cell and `0` means there is none. Two servers are said to **communicate** if they are on the same row or the same column.

Return the **number of servers that communicate with at least one other server**.

**Example 1:**
```
Input: grid = [[1,0],[0,1]]
Output: 0
Explanation: No servers can communicate with others.
```

**Example 2:**
```
Input: grid = [[1,0],[1,1]]
Output: 3
Explanation: All three servers can communicate with at least one other server.
```

**Example 3:**
```
Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
Output: 4
Explanation: The two servers in the first row communicate with each other.
             The two servers in the third column communicate with each other.
             The server at the bottom-right corner cannot communicate with any other server.
```

**Constraints:**
- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 250`
- `grid[i][j]` is `0` or `1`

---

## Observations

1. **Communication rule**: A server communicates with another if and only if they share the same row or the same column. This means a server is "connected" to the outside world purely by how many other servers live in its row or column.

2. **Isolated server definition**: A server at `(r, c)` is **isolated** (cannot communicate with anyone) if and only if it is the *only* server in row `r` **and** the *only* server in column `c`. Both conditions must hold simultaneously.

3. **Complement counting is simpler**: Instead of directly counting servers that *do* communicate, it is easier to:
   - Count the **total** number of servers in the grid, then
   - Subtract the number of **isolated** servers.

4. **Efficient precomputation**: We can count the number of servers per row and per column in a single pass over the grid using two auxiliary arrays:
   - `rows[r]` = number of servers in row `r`
   - `cols[c]` = number of servers in column `c`

5. **Single-pass isolation check**: A second pass then checks each server cell: if `rows[r] == 1` and `cols[c] == 1`, that server is isolated.

6. **No sorting, no graph traversal needed**: The problem reduces entirely to counting, making the solution linear in the grid size.

---

## Solution

**Algorithm**: Count all servers, then subtract isolated ones.

**Time Complexity**: $O(m \times n)$ — two full passes over the grid  
**Space Complexity**: $O(m + n)$ — for the `rows` and `cols` count arrays

### Step-by-step Breakdown

**Step 1 — Count servers per row and column, and total:**
```python
rows = [0] * m   # rows[r] = number of servers in row r
cols = [0] * n   # cols[c] = number of servers in column c
total = 0

for r in range(m):
    for c in range(n):
        if grid[r][c] == 1:
            rows[r] += 1
            cols[c] += 1
            total += 1
```

**Step 2 — Count isolated servers:**
```python
isolated = 0
for r in range(m):
    for c in range(n):
        if grid[r][c] == 1 and rows[r] == 1 and cols[c] == 1:
            isolated += 1
```

A server is isolated when it is the sole server in its entire row AND the sole server in its entire column — meaning there is literally no other server it can reach.

**Step 3 — Return the answer:**
```python
return total - isolated
```

### Complete Solution

```python
class Solution:
    def countServers(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        rows = [0] * m
        cols = [0] * n
        total = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    rows[r] += 1
                    cols[c] += 1
                    total += 1

        isolated = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1 and rows[r] == 1 and cols[c] == 1:
                    isolated += 1

        return total - isolated
```

### Example Walkthrough

Using **Example 3**: `grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]`

**After Step 1:**
```
rows = [2, 1, 1, 1]   (row 0 has 2 servers; rows 1,2,3 have 1 each)
cols = [1, 1, 2, 0, 1] → actually cols = [1, 1, 2, 1]
                          (col 0: 1, col 1: 1, col 2: 2, col 3: 1)
total = 5
```

**After Step 2 — checking each server for isolation:**

| Server | rows[r] | cols[c] | Isolated? |
|--------|---------|---------|-----------|
| (0,0)  | 2       | 1       | No — shares row 0 with (0,1) |
| (0,1)  | 2       | 1       | No — shares row 0 with (0,0) |
| (1,2)  | 1       | 2       | No — shares col 2 with (2,2) |
| (2,2)  | 1       | 2       | No — shares col 2 with (1,2) |
| (3,3)  | 1       | 1       | **Yes** — alone in row 3 and col 3 |

`isolated = 1`

**Answer**: `total - isolated = 5 - 1 = 4` ✓

---

## Tags

`array` `matrix` `counting`
