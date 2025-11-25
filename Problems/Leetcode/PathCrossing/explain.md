## Problem

https://leetcode.com/problems/path-crossing/description/

```
Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.

Return true if the path crosses itself at any point, that is, if at any time you are on a location you have previously visited. Return false otherwise.

Example 1:
Input: path = "NES"
Output: false 
Explanation: Notice that the path doesn't cross any point more than once.

Example 2:
Input: path = "NESWW"
Output: true
Explanation: Notice that the path visits the origin twice.

Constraints:
- 1 <= path.length <= 10^4
- path[i] is either 'N', 'S', 'E', or 'W'.
```

## Observations

1. **Coordinate System**: We need to track our position on a 2D grid starting from origin (0, 0)
2. **Movement Mapping**: Each direction corresponds to a coordinate change:
   - 'N' (North): Move up → row decreases by 1
   - 'S' (South): Move down → row increases by 1
   - 'E' (East): Move right → column increases by 1
   - 'W' (West): Move left → column decreases by 1
3. **Path Crossing Detection**: We need to detect if we visit any coordinate more than once
4. **Set for Tracking**: Using a set to store visited coordinates allows O(1) lookup time
5. **Early Termination**: We can return `true` immediately when we find a duplicate position

## Solution

**Approach: Hash Set for Visited Positions**

The solution uses a set to track all previously visited coordinates. For each step in the path:
1. Calculate the new position based on the current direction
2. Check if this position has been visited before
3. If yes, return `true` (path crosses)
4. If no, add the position to the visited set and continue

**Time Complexity**: O(n) where n is the length of the path
**Space Complexity**: O(n) for storing visited positions in the set

**Note**: There's a small correction needed in the direction mapping - 'E' should be (0, 1) and 'W' should be (0, -1) to properly represent east as right movement and west as left movement.

# Tags

array, string, hash table