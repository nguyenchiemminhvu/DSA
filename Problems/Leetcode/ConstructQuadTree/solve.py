from typing import List

class Node:
    def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
        self.val = val
        self.isLeaf = isLeaf
        self.topLeft = topLeft
        self.topRight = topRight
        self.bottomLeft = bottomLeft
        self.bottomRight = bottomRight

class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        def solve(r, c, n):
            # Check if all elements in the current square are the same
            is_same = True
            first_val = grid[r][c]
            for i in range(r, r + n):
                for j in range(c, c + n):
                    if grid[i][j] != first_val:
                        is_same = False
                        break
                if not is_same: break
            
            if is_same:
                # Leaf node: val is the actual grid value (converted to bool)
                return Node(first_val == 1, True)
            
            # Internal node: divide into 4 quadrants
            half = n // 2
            top_left = solve(r, c, half)
            top_right = solve(r, c + half, half)
            bottom_left = solve(r + half, c, half)
            bottom_right = solve(r + half, c + half, half)
            
            return Node(True, False, top_left, top_right, bottom_left, bottom_right)
            
        return solve(0, 0, len(grid))