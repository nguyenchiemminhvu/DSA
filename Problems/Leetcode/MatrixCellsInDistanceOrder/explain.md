## Problem

https://leetcode.com/problems/matrix-cells-in-distance-order/

```
You are given four integers row, cols, rCenter, and cCenter. There is a rows x cols matrix and you are on the cell with the coordinates (rCenter, cCenter).

Return the coordinates of all cells in the matrix, sorted by their distance from (rCenter, cCenter) from the smallest distance to the largest distance. You may return the answer in any order that satisfies this condition.

The distance between two cells (r1, c1) and (r2, c2) is |r1 - r2| + |c1 - c2|.

Example 1:

Input: rows = 1, cols = 2, rCenter = 0, cCenter = 0
Output: [[0,0],[0,1]]
Explanation: The distances from (0, 0) to other cells are: [0,1]

Example 2:

Input: rows = 2, cols = 2, rCenter = 0, cCenter = 1
Output: [[0,1],[0,0],[1,1],[1,0]]
Explanation: The distances from (0, 1) to other cells are: [0,1,1,2]
The answer [[0,1],[1,1],[0,0],[1,0]] would also be accepted as correct.

Example 3:

Input: rows = 2, cols = 3, rCenter = 1, cCenter = 2
Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
Explanation: The distances from (1, 2) to other cells are: [0,1,1,2,2,3]
There are other answers that would also be accepted as correct, such as [[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]].

Constraints:

1 <= rows, cols <= 100
0 <= rCenter < rows
0 <= cCenter < cols
```

## Observations

1. **Manhattan Distance**: The problem uses Manhattan distance (also called taxicab distance), which is the sum of absolute differences of coordinates: `|r1 - r2| + |c1 - c2|`

2. **Generate All Cells**: We need to generate all possible cells in the `rows × cols` matrix, which means all coordinate pairs `(i, j)` where `0 ≤ i < rows` and `0 ≤ j < cols`

3. **Sort by Distance**: Once we have all cells, we need to sort them by their Manhattan distance from the center point `(rCenter, cCenter)`

4. **Multiple Valid Answers**: Cells with the same distance can be returned in any order, so there are multiple correct answers possible

5. **Simple Approach**: The most straightforward approach is to generate all cells and sort them using the distance as the key

## Solution

1. **List Comprehension**: `[[i, j] for i in range(rows) for j in range(cols)]` generates all possible cell coordinates in the matrix
   - Creates a nested loop: for each row `i` from 0 to `rows-1`, for each column `j` from 0 to `cols-1`
   - Results in a list of `[row, column]` pairs representing all cells

2. **Sorting with Custom Key**: Uses `sorted()` with a lambda function as the key
   - `key=lambda x: abs(x[0] - rCenter) + abs(x[1] - cCenter)` calculates Manhattan distance
   - `x[0]` is the row coordinate, `x[1]` is the column coordinate
   - `abs(x[0] - rCenter)` gives the vertical distance
   - `abs(x[1] - cCenter)` gives the horizontal distance
   - Sum gives total Manhattan distance from center

3. **Time Complexity**: O(RC log RC) where R = rows, C = cols
   - Generating all cells: O(RC)
   - Sorting RC elements: O(RC log RC)

4. **Space Complexity**: O(RC) for storing all cell coordinates

**Alternative Approaches:**
- **BFS**: Start from center and expand layer by layer (more complex but potentially more intuitive)
- **Bucket Sort**: Group cells by distance and concatenate (O(RC) time but requires knowing max distance)

# Tags

- **Array**
- **Sorting** 
- **Manhattan Distance**
- **Matrix**

