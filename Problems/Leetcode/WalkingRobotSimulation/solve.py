from typing import List

class Solution:
    def robotSim(self, commands: List[int], obstacles: List[List[int]]) -> int:
        # Directions: N, E, S, W
        dirs = [(0,1), (1,0), (0,-1), (-1,0)]
        dir_idx = 0  # start facing North
        
        # Convert obstacles to set for fast lookup
        obstacle_set = set(map(tuple, obstacles))
        
        x = y = 0
        max_dist = 0
        
        for cmd in commands:
            if cmd == -1:  # turn right
                dir_idx = (dir_idx + 1) % 4
            elif cmd == -2:  # turn left
                dir_idx = (dir_idx + 3) % 4
            else:
                dx, dy = dirs[dir_idx]
                
                for _ in range(cmd):
                    nx, ny = x + dx, y + dy
                    
                    if (nx, ny) in obstacle_set:
                        break
                    
                    x, y = nx, ny
                    max_dist = max(max_dist, x*x + y*y)
        
        return max_dist