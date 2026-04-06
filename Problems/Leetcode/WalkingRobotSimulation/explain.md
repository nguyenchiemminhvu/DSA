## Problem

https://leetcode.com/problems/walking-robot-simulation/description/

A robot starts at point (0, 0) on an infinite 2D grid, facing north. The robot receives a sequence of commands:
- `-2`: Turn left 90 degrees
- `-1`: Turn right 90 degrees  
- `1-9`: Move forward k units, one unit at a time

Some grid squares contain obstacles. When the robot would move into an obstacle, it stops at the adjacent position and continues with the next command.

**Goal**: Return the maximum squared Euclidean distance that the robot reaches at any point during its path.

**Key constraints**:
- Obstacles at (0, 0) are ignored until the robot leaves the origin
- Answer is guaranteed to be less than 2³¹

## Observations

1. **Direction representation**: Instead of storing angles, use direction vectors (dx, dy) for the four cardinal directions: North (0,1), East (1,0), South (0,-1), West (-1,0).

2. **Direction rotation**: 
   - Turn right: `dir_idx = (dir_idx + 1) % 4`
   - Turn left: `dir_idx = (dir_idx + 3) % 4` (equivalent to -1 with modulo wrapping)

3. **Obstacle lookup**: Convert obstacles list to a set for O(1) lookup time, avoiding the O(n) overhead of list searches.

4. **Step-by-step movement**: When moving k units, check for obstacles at each intermediate position, not just the final destination. The robot stops immediately before hitting an obstacle.

5. **Track maximum distance**: The maximum distance must be checked after **every single step**, not just after each command, because the furthest point might be in the middle of a multi-step movement.

6. **Special case**: The obstacle at (0, 0) is special—it doesn't block the starting position, only subsequent entries to it.

## Solution

```python
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
```

**Algorithm explanation**:

1. **Setup**: Define direction vectors indexed by current direction. Initialize at (0,0) facing north (dir_idx=0).

2. **Process each command**:
   - If `-1` (turn right): increment direction index modulo 4
   - If `-2` (turn left): add 3 to direction index modulo 4 (same as subtracting 1 with wrap-around)
   - If positive: move one unit at a time in the current direction

3. **Movement logic**: For each step forward:
   - Calculate next position (nx, ny)
   - Check if it's an obstacle
   - If obstacle exists, stop and break (don't move)
   - If no obstacle, move there and update max distance

4. **Return**: The maximum squared distance encountered

**Complexity**:
- **Time**: O(n + m) where n = total steps across all commands, m = number of obstacles
  - Each command step checks one obstacle lookup: O(1)
  - Total command steps is at most 9 × 10⁴ = 90,000
- **Space**: O(m) for the obstacle set

**Example walkthrough** (commands = [4,-1,3], obstacles = []):
- Start: (0,0) facing N
- Move 4 north: (0,1)→(0,2)→(0,3)→(0,4), max_dist=16
- Turn right: facing E
- Move 3 east: (1,4)→(2,4)→(3,4), max_dist=25 ✓

# Tags
- Graph/Grid Traversal
- Direction Vectors
- Set/Hash
- Simulation

