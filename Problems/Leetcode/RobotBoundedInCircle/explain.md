## Problem

https://leetcode.com/problems/robot-bounded-in-circle/description

A robot starts at position (0, 0) on an infinite plane, facing north. It receives a sequence of instructions that it repeats infinitely:
- `"G"`: Move 1 unit forward in the current direction
- `"L"`: Turn 90° counter-clockwise
- `"R"`: Turn 90° clockwise

**Determine if the robot will remain bounded within a circle** (never escape to infinity).

**Examples:**
- Input: `"GGLLGG"` → Output: `true` (robot cycles: (0,0) → (0,1) → (0,2) → (0,1) → (0,0))
- Input: `"GG"` → Output: `false` (robot moves indefinitely north)
- Input: `"GL"` → Output: `true` (robot forms a square cycle)

## Observations

1. **Cyclical Nature**: After executing the instruction sequence once, the robot either:
   - Returns to origin with same direction → bounded (cycle length = 1)
   - Returns to origin with different direction → bounded (cycle will complete in ≤4 iterations)
   - Stays at origin but changed direction → bounded (will return after multiple rotations)
   - Doesn't return to origin but changed direction → bounded (rotated position will cycle)

2. **Key Insight**: If the robot doesn't return to (0,0) after **one** sequence, it can still be bounded if it's facing a direction other than north. This is because:
   - Facing north after sequence: unbounded (keeps moving in same direction)
   - Facing any other direction: eventually bounded (rotation causes the offset to trace a cycle)

3. **4-Iteration Guarantee**: After 4 complete iterations of the instruction sequence, if the robot returns to (0,0), it's definitely bounded. This covers all possible cyclic patterns:
   - 1-cycle: robot returns after 1st iteration
   - 2-cycle: robot returns after 2nd iteration  
   - 4-cycle: robot returns after 4th iteration
   - All intermediate cases are covered

## Solution

```python
class Solution:
    def isRobotBounded(self, commands: str) -> bool:
        # Direction vectors: North, East, South, West
        dir_x = [0, 1, 0, -1]   # x displacement for each direction
        dir_y = [1, 0, -1, 0]   # y displacement for each direction
        
        x, y = 0, 0             # Robot position
        idir = 0                # Direction index (0=North, 1=East, 2=South, 3=West)
        
        # Execute instruction sequence 4 times
        for time in range(4):
            for command in commands:
                if command == 'L':
                    # Turn left: direction index decreases (with wraparound)
                    idir = (idir - 1 + 4) % 4
                elif command == 'R':
                    # Turn right: direction index increases (with wraparound)
                    idir = (idir + 1) % 4
                else:  # command == 'G'
                    # Move forward in current direction
                    x += dir_x[idir]
                    y += dir_y[idir]
        
        # If robot returns to origin after 4 iterations, it's bounded
        return x == 0 and y == 0
```

### Algorithm Explanation

**Direction Tracking:**
- Use index `idir` to represent the robot's facing direction:
  - 0 = North (positive y)
  - 1 = East (positive x)
  - 2 = South (negative y)
  - 3 = West (negative x)
- `dir_x` and `dir_y` arrays store the displacement for each direction

**Command Processing:**
- 'L': Rotate counter-clockwise: `idir = (idir - 1 + 4) % 4`
- 'R': Rotate clockwise: `idir = (idir + 1) % 4`
- 'G': Move: `x += dir_x[idir]`, `y += dir_y[idir]`

**Multiple Iterations:**
- Execute the entire instruction sequence 4 times
- After 4 iterations, if position is (0,0), the robot is bounded
- The 4-iteration approach accounts for all possible cycle lengths

**Complexity Analysis:**
- Time: $O(4 \times |commands|) = O(n)$ where $n$ is instruction length
- Space: $O(1)$ (only tracking position and direction)

### Why 4 Iterations Work

After one sequence, the robot can be in one of these states:
1. **At (0,0) facing North**: Unbounded (keeps repeating same path infinitely north)
2. **At (0,0) facing any other direction**: Bounded (rotated repeat will eventually close)
3. **Not at (0,0) facing any direction**: 
   - If facing North: Unbounded (displacement repeats forever)
   - If facing any other direction: Bounded (rotations cause the pattern to form a closed loop within 4 iterations)

# Tags
- Math/Simulation
- Direction/Angle Management
- Cycle Detection
- Simulation

