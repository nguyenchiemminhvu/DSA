## Problem

https://leetcode.com/problems/design-neighbor-sum-service/description/

```
You are given a n x n 2D array grid containing distinct elements in the range [0, n2 - 1].

Implement the NeighborSum class:

NeighborSum(int [][]grid) initializes the object.
int adjacentSum(int value) returns the sum of elements which are adjacent neighbors of value, that is either to the top, left, right, or bottom of value in grid.
int diagonalSum(int value) returns the sum of elements which are diagonal neighbors of value, that is either to the top-left, top-right, bottom-left, or bottom-right of value in grid.

Example 1:

Input:

["NeighborSum", "adjacentSum", "adjacentSum", "diagonalSum", "diagonalSum"]

[[[[0, 1, 2], [3, 4, 5], [6, 7, 8]]], [1], [4], [4], [8]]

Output: [null, 6, 16, 16, 4]

Explanation:

The adjacent neighbors of 1 are 0, 2, and 4.
The adjacent neighbors of 4 are 1, 3, 5, and 7.
The diagonal neighbors of 4 are 0, 2, 6, and 8.
The diagonal neighbor of 8 is 4.

Example 2:

Input:

["NeighborSum", "adjacentSum", "diagonalSum"]

[[[[1, 2, 0, 3], [4, 7, 15, 6], [8, 9, 10, 11], [12, 13, 14, 5]]], [15], [9]]

Output: [null, 23, 45]

Explanation:

The adjacent neighbors of 15 are 0, 10, 7, and 6.
The diagonal neighbors of 9 are 4, 12, 14, and 15.

Constraints:

3 <= n == grid.length == grid[0].length <= 10
0 <= grid[i][j] <= n2 - 1
All grid[i][j] are distinct.
value in adjacentSum and diagonalSum will be in the range [0, n2 - 1].
At most 2 * n2 calls will be made to adjacentSum and diagonalSum.
```

## Observations

1. **Problem Understanding**: We need to design a service that can efficiently calculate sums of adjacent and diagonal neighbors for any given value in an n×n grid.

2. **Key Constraints**:
   - Grid contains distinct values from 0 to n²-1
   - Grid size is 3×3 to 10×10 (small)
   - At most 2×n² queries will be made
   - All values are unique in the grid

3. **Neighbor Definitions**:
   - **Adjacent neighbors**: Up, Down, Left, Right (4-directional)
   - **Diagonal neighbors**: Top-left, Top-right, Bottom-left, Bottom-right (4-diagonal)

4. **Edge Cases**:
   - Elements on borders/corners have fewer neighbors
   - Need boundary checking for all neighbor positions

## Solution

### Approach: Preprocessing + Direct Lookup

The solution uses a preprocessing approach with O(1) query time:

1. **Initialization Phase** (`__init__`):
   - Store a copy of the grid
   - Create a hashmap `self.map` to store value → (row, col) mapping
   - This allows O(1) position lookup for any value

2. **Query Phase** (both `adjacentSum` and `diagonalSum`):
   - Use the hashmap to get position of the target value
   - Generate all possible neighbor coordinates
   - Check boundaries and sum valid neighbors

### Time & Space Complexity:

- **Time Complexity**:
  - Initialization: O(n²) - iterate through grid once
  - adjacentSum/diagonalSum: O(1) - constant 4 neighbor checks
  
- **Space Complexity**: 
  - O(n²) for storing the grid copy and hashmap

### Alternative Approaches:

1. **Store precomputed sums**: Could precompute adjacent and diagonal sums for all values during initialization for true O(1) queries, but uses more space.

2. **Linear search each query**: Search for value position each time - O(n²) per query, much slower.

### Why This Solution Works Well:

- **Efficient for multiple queries**: The preprocessing step pays off when we have multiple sum queries
- **Simple and readable**: Clear separation of concerns
- **Handles edge cases**: Proper boundary checking prevents array out-of-bounds
- **Space-time tradeoff**: Uses O(n²) extra space for O(1) query time

# Tags

**Grid, Hash Table, Design, Preprocessing**

