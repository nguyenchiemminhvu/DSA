## Problem

https://leetcode.com/problems/cyclically-rotating-a-grid/description/

You are given an m × n integer matrix `grid`, where both m and n are even integers, and an integer `k`.

The matrix is composed of several concentric layers. A cyclic rotation of the matrix is performed by rotating each layer independently in the counter-clockwise direction. Each element in a layer moves to the position of the adjacent element in the counter-clockwise direction.

**Task:** Return the matrix after applying k cyclic rotations to it.

**Constraints:**
- m == grid.length (2 ≤ m ≤ 50)
- n == grid[i].length (2 ≤ n ≤ 50)
- Both m and n are even integers
- 1 ≤ grid[i][j] ≤ 5000
- 1 ≤ k ≤ 10^9

**Examples:**

Example 1: `grid = [[40,10],[30,20]], k = 1` → Output: `[[10,20],[40,30]]`

Example 2: `grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], k = 2` → Output: `[[3,4,8,12],[2,11,10,16],[1,7,6,15],[5,9,13,14]]`

## Observations

1. **Layer Decomposition:** The matrix can be conceptually decomposed into concentric layers. The outermost layer, next layer inward, and so on. Each layer forms a cycle of elements.

2. **Independent Rotation:** Since each layer rotates independently, we can extract each layer, rotate it, and place it back. This reduces the problem to rotating 1D arrays.

3. **Modulo Optimization:** Since k can be extremely large (up to 10^9), rotating a layer with n elements by k steps is equivalent to rotating by k % n steps. This avoids unnecessary iterations.

4. **Counter-Clockwise vs Clockwise:** Counter-clockwise rotation in a layer means elements move forward in the extraction order. If we extract elements going: top row (left to right), right column (top to bottom), bottom row (right to left), left column (bottom to top), then a counter-clockwise rotation shifts all elements forward in this sequence.

5. **Layer Count:** The total number of layers is `min(m, n) // 2` since both m and n are even. Each layer peels off one row from top and bottom, and one column from left and right.

6. **Time Complexity:** O(m × n) for extraction and filling, plus O(number of elements) for rotation. Despite k being large, the modulo operation keeps actual rotation work minimal.

7. **Space Complexity:** O(m × n) for storing all layers.

## Solution

### Approach: Layer Extraction, Rotation, and Reconstruction

The solution works in three main steps:

**Step 1: Extract Layers**

The `get_layers()` function decomposes the matrix into concentric layers. For each layer `l`, we identify its boundaries:
- `top = l`, `bottom = m - 1 - l` (vertical bounds)
- `left = l`, `right = n - 1 - l` (horizontal bounds)

Elements are extracted in counter-clockwise order:
1. **Top row:** From left to right (left → right)
2. **Right column:** From top+1 to bottom-1 (top → bottom, excluding corners)
3. **Bottom row:** From right to left (right → left, including corner)
4. **Left column:** From bottom-1 to top+1 (bottom → top, excluding corners)

This ordering ensures that adjacent elements in the extracted list are adjacent in the matrix layer.

```python
def get_layers(grid):
    m, n = len(grid), len(grid[0])
    layers = []
    
    for l in range(min(m, n) // 2):
        layer = []
        top, bottom = l, m - 1 - l
        left, right = l, n - 1 - l
        
        # Extract in counter-clockwise order
        for j in range(left, right + 1):
            layer.append(grid[top][j])
        for i in range(top + 1, bottom):
            layer.append(grid[i][right])
        for j in range(right, left - 1, -1):
            layer.append(grid[bottom][j])
        for i in range(bottom - 1, top, -1):
            layer.append(grid[i][left])
        
        layers.append(layer)
    
    return layers
```

**Step 2: Rotate Each Layer**

For each layer with n elements, we compute the effective rotation count as `k % n`. This optimization ensures we only perform necessary rotations, even if k is very large.

Counter-clockwise rotation by k positions is achieved by moving the first k elements to the end:
```python
layers[i] = layer[k_mod:] + layer[:k_mod]
```

This shifts all elements forward in the layer's cycle, achieving the counter-clockwise effect.

**Step 3: Reconstruct the Matrix**

The `fill_layers()` function reverses the extraction process. Using the same boundary traversal as extraction, it places rotated elements back into the matrix in their new positions:

```python
def fill_layers(grid, layers):
    m, n = len(grid), len(grid[0])
    
    for l in range(len(layers)):
        layer = layers[l]
        idx = 0
        top, bottom = l, m - 1 - l
        left, right = l, n - 1 - l
        
        # Fill in the same counter-clockwise order
        for j in range(left, right + 1):
            grid[top][j] = layer[idx]
            idx += 1
        for i in range(top + 1, bottom):
            grid[i][right] = layer[idx]
            idx += 1
        for j in range(right, left - 1, -1):
            grid[bottom][j] = layer[idx]
            idx += 1
        for i in range(bottom - 1, top, -1):
            grid[i][left] = layer[idx]
            idx += 1
```

### Complete Solution

```python
class Solution:
    def rotateGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:
        def get_layers(grid):
            m, n = len(grid), len(grid[0])
            layers = []
            
            for l in range(min(m, n) // 2):
                layer = []
                
                top, bottom = l, m - 1 - l
                left, right = l, n - 1 - l
                
                # Top row (left to right)
                for j in range(left, right + 1):
                    layer.append(grid[top][j])
                
                # Right column (top+1 to bottom-1)
                for i in range(top + 1, bottom):
                    layer.append(grid[i][right])
                
                # Bottom row (right to left)
                for j in range(right, left - 1, -1):
                    layer.append(grid[bottom][j])
                
                # Left column (bottom-1 to top+1)
                for i in range(bottom - 1, top, -1):
                    layer.append(grid[i][left])
                
                layers.append(layer)
            
            return layers
        
        def fill_layers(grid, layers):
            m, n = len(grid), len(grid[0])
            
            for l in range(len(layers)):
                layer = layers[l]
                idx = 0
                
                top, bottom = l, m - 1 - l
                left, right = l, n - 1 - l
                
                # Fill top row
                for j in range(left, right + 1):
                    grid[top][j] = layer[idx]
                    idx += 1
                
                # Fill right column
                for i in range(top + 1, bottom):
                    grid[i][right] = layer[idx]
                    idx += 1
                
                # Fill bottom row
                for j in range(right, left - 1, -1):
                    grid[bottom][j] = layer[idx]
                    idx += 1
                
                # Fill left column
                for i in range(bottom - 1, top, -1):
                    grid[i][left] = layer[idx]
                    idx += 1
        
        m, n = len(grid), len(grid[0])
        
        # Extract all layers
        layers = get_layers(grid)
        
        # Rotate each layer by k positions
        for i in range(len(layers)):
            layer = layers[i]
            k_mod = k % len(layer)  # Optimize: only rotate by k % layer_size
            layers[i] = layer[k_mod:] + layer[:k_mod]
        
        # Reconstruct the matrix with rotated layers
        fill_layers(grid, layers)
        
        return grid
```

### Complexity Analysis

- **Time Complexity:** O(m × n) — We visit each cell once during extraction and once during reconstruction. The rotation operation (list slicing and concatenation) is also O(m × n) in total across all layers.
  
- **Space Complexity:** O(m × n) — We store all elements in the `layers` list.

### Key Insights

1. The modulo operation (`k % len(layer)`) is critical for handling large k values efficiently.
2. Extracting elements in order and rotating the 1D array simplifies the problem significantly compared to trying to rotate elements in-place.
3. The extraction and filling follow the same pattern, ensuring correctness when reconstructing the matrix.

# Tags

