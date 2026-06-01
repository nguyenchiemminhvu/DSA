## Problem

https://leetcode.com/problems/sort-the-matrix-diagonally/description/

Given an `m x n` matrix `mat` of integers, sort each **matrix diagonal** in ascending order and return the resulting matrix.

A **matrix diagonal** starts from a cell in either the topmost row or the leftmost column, and extends in the bottom-right direction until it goes out of bounds.

**Example 1:**
```
Input:  mat = [[3,3,1,1],
               [2,2,1,2],
               [1,1,1,2]]

Output:        [[1,1,1,1],
                [1,2,2,2],
                [1,2,3,3]]
```

**Example 2:**
```
Input:  mat = [[11,25,66, 1,69, 7],
               [23,55,17,45,15,52],
               [75,31,36,44,58, 8],
               [22,27,33,25,68, 4],
               [84,28,14,11, 5,50]]

Output:        [[ 5,17, 4, 1,52, 7],
                [11,11,25,45, 8,69],
                [14,23,25,44,58,15],
                [22,27,31,36,50,66],
                [84,28,75,33,55,68]]
```

**Constraints:**
- `1 <= m, n <= 100`
- `1 <= mat[i][j] <= 100`

---

## Observations

1. **Diagonal identity:** Every cell `mat[r][c]` belongs to the diagonal identified by `r - c`. Cells sharing the same `r - c` value lie on the same diagonal.

2. **Number of diagonals:** For an `m x n` matrix there are `m + n - 1` distinct diagonals in total. Their starting points are either in the first column (`(i, 0)` for `i = 0..m-1`) or the first row (`(0, j)` for `j = 1..n-1`).

3. **Sort in place:** For each diagonal we can collect all values into a temporary list, sort it, then write the sorted values back along the same path.

4. **Small constraints:** With `m, n ≤ 100` the total number of cells is at most `10 000`, so even an $O(mn \log(\min(m,n)))$ approach is well within time limits.

---

## Solution Explanation

### Helper — `sort_diag(r_start, c_start)`

```
collect:  traverse (r_start, c_start) → (r_start+k, c_start+k) while in-bounds
          append mat[r][c] to a temporary list
sort:     sort the temporary list ascending
write:    put sorted values back along the same diagonal cells
```

### Main logic

We need to cover every diagonal exactly once. The set of all diagonal starting points is:

| Starting cells | Diagonals covered |
|---|---|
| `(i, 0)` for `i = 0 … m-1` | all diagonals whose top-left anchor is in the **leftmost column** |
| `(0, j)` for `j = 1 … n-1` | all diagonals whose top-left anchor is in the **topmost row** (excluding the main diagonal already covered by `j=0` above) |

```
for i in 0..m-1:   sort_diag(i, 0)   # diagonals starting on left edge
for j in 1..n-1:   sort_diag(0, j)   # diagonals starting on top edge
```

### Walkthrough on Example 1

```
Original:
  3  3  1  1
  2  2  1  2
  1  1  1  2

Diagonals (r-c key → cells):
  -2 → [1]          (1,0)→(2,0)  (only mat[2][0]=1)
  -1 → [2,1]        mat[1][0], mat[2][1]
   0 → [3,2,1]      main diagonal
   1 → [3,1,2]      mat[0][1], mat[1][2], mat[2][3]
   2 → [1,2]        mat[0][2], mat[1][3]
   3 → [1]          mat[0][3]

After sorting each diagonal:
  1  1  1  1
  1  2  2  2
  1  2  3  3  ✓
```

### Complexity

| | |
|---|---|
| **Time** | $O(mn \log(\min(m, n)))$ — each cell visited once; each diagonal of length $L$ costs $O(L \log L)$ |
| **Space** | $O(\min(m, n))$ — temporary list for one diagonal at a time |

---

## Code

```python
class Solution:
    def diagonalSort(self, mat: List[List[int]]) -> List[List[int]]:
        m, n = len(mat), len(mat[0])

        def sort_diag(r_start: int, c_start: int) -> List[int]:
            res = []
            r, c = r_start, c_start
            while r < m and c < n:
                res.append(mat[r][c])
                r += 1
                c += 1
            res.sort()
            r, c = r_start, c_start
            for i in range(len(res)):
                mat[r + i][c + i] = res[i]
            return res

        for i in range(m):       # diagonals starting in the left column
            sort_diag(i, 0)

        for j in range(1, n):    # diagonals starting in the top row (skip (0,0))
            sort_diag(0, j)

        return mat
```
