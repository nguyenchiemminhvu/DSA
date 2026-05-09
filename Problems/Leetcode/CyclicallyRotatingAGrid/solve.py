from typing import List

class Solution:
    def rotateGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:
        def get_layers(grid):
            m, n = len(grid), len(grid[0])
            layers = []
            
            for l in range(min(m, n) // 2):
                layer = []
                
                top, bottom = l, m - 1 - l
                left, right = l, n - 1 - l
                
                # 1. top row
                for j in range(left, right + 1):
                    layer.append(grid[top][j])
                
                # 2. right column
                for i in range(top + 1, bottom):
                    layer.append(grid[i][right])
                
                # 3. bottom row
                for j in range(right, left - 1, -1):
                    layer.append(grid[bottom][j])
                
                # 4. left column
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
                
                # 1. top row
                for j in range(left, right + 1):
                    grid[top][j] = layer[idx]
                    idx += 1
                
                # 2. right column
                for i in range(top + 1, bottom):
                    grid[i][right] = layer[idx]
                    idx += 1
                
                # 3. bottom row
                for j in range(right, left - 1, -1):
                    grid[bottom][j] = layer[idx]
                    idx += 1
                
                # 4. left column
                for i in range(bottom - 1, top, -1):
                    grid[i][left] = layer[idx]
                    idx += 1
        
        m, n = len(grid), len(grid[0])
        
        # Step 1: extract layers
        layers = get_layers(grid)
        
        # Step 2: rotate each layer
        for i in range(len(layers)):
            layer = layers[i]
            k_mod = k % len(layer)
            layers[i] = layer[k_mod:] + layer[:k_mod]  # counter-clockwise
        
        # Step 3: put back
        fill_layers(grid, layers)
        
        return grid