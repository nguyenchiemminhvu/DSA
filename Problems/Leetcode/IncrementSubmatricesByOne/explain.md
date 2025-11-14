## Problem

https://leetcode.com/problems/increment-submatrices-by-one/description/

```
You are given a positive integer n, indicating that we initially have an n x n 0-indexed integer matrix mat filled with zeroes.

You are also given a 2D integer array query. For each query[i] = [row1i, col1i, row2i, col2i], you should do the following operation:

Add 1 to every element in the submatrix with the top left corner (row1i, col1i) and the bottom right corner (row2i, col2i). That is, add 1 to mat[x][y] for all row1i <= x <= row2i and col1i <= y <= col2i.
Return the matrix mat after performing every query.

Example 1:

Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
Output: [[1,1,0],[1,2,1],[0,1,1]]
Explanation: The diagram above shows the initial matrix, the matrix after the first query, and the matrix after the second query.
- In the first query, we add 1 to every element in the submatrix with the top left corner (1, 1) and bottom right corner (2, 2).
- In the second query, we add 1 to every element in the submatrix with the top left corner (0, 0) and bottom right corner (1, 1).

Example 2:

Input: n = 2, queries = [[0,0,1,1]]
Output: [[1,1],[1,1]]
Explanation: The diagram above shows the initial matrix and the matrix after the first query.
- In the first query we add 1 to every element in the matrix.

Constraints:

1 <= n <= 500
1 <= queries.length <= 104
0 <= row1i <= row2i < n
0 <= col1i <= col2i < n
```

## Observations

1. **Problem Understanding**: We start with an n×n matrix filled with zeros and need to perform range updates where each query adds 1 to all elements in a rectangular submatrix defined by top-left (row1, col1) and bottom-right (row2, col2) corners.

2. **Naive Approach Issues**: A straightforward approach would be to iterate through each query and update all elements in the specified submatrix. This would have O(queries × n²) time complexity in the worst case, which could be inefficient for large inputs.

3. **Optimization Opportunity**: Since we're dealing with range updates on a 2D array, we can use a difference array technique combined with prefix sum to optimize the solution.

4. **Key Insight**: Instead of updating each element individually, we can use a differential approach where we mark the start and end of increments, then compute the final values using prefix sums.

5. **Constraints Analysis**: With n ≤ 500 and queries ≤ 10⁴, we need an efficient solution. The given solution uses O(queries × n + n²) time complexity, which is acceptable.

## Solution

The solution uses a **differential array technique** combined with **prefix sum computation**:

### Algorithm Steps:

1. **Initialize Differential Array**: Create an n×n matrix `prefix` initialized with zeros to store differential values.

2. **Process Queries Using Range Update Technique**:
   - For each query `[a, b, c, d]` (top-left to bottom-right):
   - For each row `r` from `a` to `c`:
     - Add 1 at column `b` (start of range): `prefix[r][b] += 1`
     - Subtract 1 at column `d+1` (end of range): `prefix[r][d+1] -= 1`
   - This marks the boundaries where increments start and end

3. **Compute Prefix Sums**:
   - For each row, compute the prefix sum from left to right
   - This converts the differential array into the actual result matrix

### How It Works:

The technique leverages the **range update in O(1)** principle:
- Instead of updating all elements in a range, we mark the start (+1) and end (-1) of the range
- When we compute prefix sums, all elements between start and end get incremented by 1

### Example Walkthrough:
For `n = 3, queries = [[1,1,2,2],[0,0,1,1]]`:

**Step 1**: Process first query [1,1,2,2]
```
Row 1: +1 at col 1, -1 at col 3 (out of bounds, ignored)
Row 2: +1 at col 1, -1 at col 3 (out of bounds, ignored)
```

**Step 2**: Process second query [0,0,1,1]  
```
Row 0: +1 at col 0, -1 at col 2
Row 1: +1 at col 0, -1 at col 2
```

**Step 3**: Compute prefix sums for each row to get final result.

### Time Complexity:
- Processing queries: O(queries × n)
- Computing prefix sums: O(n²)
- **Total**: O(queries × n + n²)

### Space Complexity: O(n²) for the result matrix

# Tags

- **Array Manipulation**
- **Prefix Sum**
- **Differential Array**
- **Range Updates**
- **Matrix Operations**

