## Problem

https://leetcode.com/problems/flood-fill/

```
You are given an image represented by an m x n grid of integers image, where image[i][j] represents the pixel value of the image. You are also given three integers sr, sc, and color. Your task is to perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill:

Begin with the starting pixel and change its color to color.
Perform the same process for each pixel that is directly adjacent (pixels that share a side with the original pixel, either horizontally or vertically) and shares the same color as the starting pixel.
Keep repeating this process by checking neighboring pixels of the updated pixels and modifying their color if it matches the original color of the starting pixel.
The process stops when there are no more adjacent pixels of the original color to update.
Return the modified image after performing the flood fill.

Example 1:

Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2

Output: [[2,2,2],[2,2,0],[2,0,1]]

Explanation:

From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.

Note the bottom corner is not colored 2, because it is not horizontally or vertically connected to the starting pixel.

Example 2:

Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0

Output: [[0,0,0],[0,0,0]]

Explanation:

The starting pixel is already colored with 0, which is the same as the target color. Therefore, no changes are made to the image.

Constraints:

m == image.length
n == image[i].length
1 <= m, n <= 50
0 <= image[i][j], color < 216
0 <= sr < m
0 <= sc < n
```

## Observations

1. **Flood Fill is a Classic Graph Traversal Problem**: This is essentially finding all connected components in a grid where "connected" means adjacent cells with the same color.

2. **Edge Case Handling**: If the starting pixel already has the target color, no changes should be made (as shown in Example 2).

3. **Boundary Checking**: Need to ensure we don't go out of bounds when checking adjacent cells.

4. **Visited Tracking**: Important to track visited cells to avoid infinite loops and redundant processing.

5. **4-Directional Movement**: Only horizontal and vertical neighbors are considered (not diagonal).

6. **BFS vs DFS**: Both approaches work, but BFS processes level by level while DFS goes deep first.

## Solution

**Algorithm**: Breadth-First Search (BFS) with level-by-level processing

**Key Components**:
1. **Initialization**: Store original color, create visited matrix, initialize queue with starting position
2. **BFS Traversal**: Process nodes level by level using a queue
3. **Color Change**: Change current pixel to new color
4. **Neighbor Exploration**: Check all 4 adjacent directions (up, down, left, right)
5. **Validation**: Ensure neighbors are within bounds, have original color, and haven't been visited

**Time Complexity**: `O(m × n)` - In worst case, we visit every pixel once
**Space Complexity**: `O(m × n)` - For the visited matrix and queue storage

**Potential Optimizations**:
1. **Early Return**: Add check `if orig_color == color: return image` to handle the case where target color is same as original
2. **Space Optimization**: Instead of using a separate visited matrix, you could modify the image in-place and use the color change as the visited marker
3. **Queue Efficiency**: Using `collections.deque` would be more efficient than `list.pop(0)` which is `O(n)`

**Alternative Approach**: `DFS` (Depth-First Search) could also be used with recursion or an explicit stack, which might use less memory for the queue but same overall space complexity.

## Tags

array, bfs