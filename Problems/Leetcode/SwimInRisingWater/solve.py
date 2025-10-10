import heapq

class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        INF = 0x7FFFFFFF
        m = len(grid)
        n = len(grid[0])
        def dijkstra_get_path(start_node: List[int], end_node: List[int]) -> List[Tuple[int, int]]:
            min_heights = {} # (row, col) -> min_height
            parents = {} # (row, col) -> (parent_row, parent_col)
            for i in range(m):
                for j in range(n):
                    min_heights[(i, j)] = INF
                    parents[(i, j)] = None
            min_heights[(0, 0)] = grid[0][0]
            Q = [(grid[start_node[0]][start_node[1]], start_node)]

            while len(Q) > 0:
                h, (r, c) = heapq.heappop(Q)

                if h > min_heights.get((r, c), INF):
                    continue
                
                if (r, c) == end_node:
                    break

                neighbors = [(r-1, c), (r+1, c), (r, c-1), (r, c+1)]
                for next_r, next_c in neighbors:
                    if next_r >= 0 and next_r < m and next_c >= 0 and next_c < n:
                        next_h = max(h, grid[next_r][next_c])
                        if next_h < min_heights[(next_r, next_c)]:
                            min_heights[(next_r, next_c)] = next_h
                            parents[(next_r, next_c)] = (r, c)
                            heapq.heappush(Q, (next_h, (next_r, next_c)))
            
            return min_heights[end_node]
        
        res = dijkstra_get_path((0, 0), (m-1, n-1))
        return res