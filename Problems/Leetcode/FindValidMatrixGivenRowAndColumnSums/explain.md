# 🧩 Problem: Restore Matrix from Row and Column Sums

You are given two arrays:

- `rowSum[i]`: the sum of elements in the **i-th row**
- `colSum[j]`: the sum of elements in the **j-th column**

Your task is to construct **any** matrix of size `m x n` (where `m = len(rowSum)` and `n = len(colSum)`) such that:

- All elements are **non-negative integers**
- Each row sum matches `rowSum`
- Each column sum matches `colSum`

It is guaranteed that at least one valid solution exists.

---

## 🔍 Observations

1. **Total Sum Must Match**
   - The total of all row sums must equal the total of all column sums:
     ```
     sum(rowSum) == sum(colSum)
     ```
   - This guarantees a valid solution exists.

2. **Greedy Placement Works**
   - At each cell `(i, j)`, we can safely place:
     ```
     min(rowSum[i], colSum[j])
     ```
   - Why?
     - We cannot exceed either the remaining row sum or column sum.
     - This ensures constraints are always respected.

3. **Progression Strategy**
   - Start from the top-left `(0,0)`
   - Fill values greedily
   - Move:
     - **down (i++)** when a row is satisfied
     - **right (j++)** when a column is satisfied

4. **Always Valid**
   - This greedy strategy never blocks future placements because:
     - We only reduce available sums
     - Constraints remain consistent

---

## 💡 Solution Approach (Greedy)

1. Initialize an empty matrix `grid[m][n]` filled with `0`
2. Use two pointers:
   - `i` → row index
   - `j` → column index
3. While inside bounds:
   - Assign:
     ```
     val = min(rowSum[i], colSum[j])
     ```
   - Update:
     ```
     grid[i][j] = val
     rowSum[i] -= val
     colSum[j] -= val
     ```
4. Move:
   - If `rowSum[i] == 0` → move to next row (`i += 1`)
   - Else → move to next column (`j += 1`)

---

## ⏱️ Complexity

- **Time:** `O(m * n)`
- **Space:** `O(m * n)` for the result matrix

---

## ✅ Implementation

```python
class Solution:
    def restoreMatrix(self, row_sum: List[int], col_sum: List[int]) -> List[List[int]]:
        m = len(row_sum)
        n = len(col_sum)

        grid = [[0] * n for _ in range(m)]
        i, j = 0, 0

        while i < m and j < n:
            min_val = min(row_sum[i], col_sum[j])
            grid[i][j] += min_val

            row_sum[i] -= min_val
            col_sum[j] -= min_val

            if row_sum[i] == 0:
                i += 1
            else:
                j += 1
        
        return grid
```
