## Problem

https://leetcode.com/problems/count-covered-buildings/description/

```
You are given a positive integer n, representing an n x n city. You are also given a 2D grid buildings, 
where buildings[i] = [x, y] denotes a unique building located at coordinates [x, y].

A building is covered if there is at least one building in all four directions: left, right, above, and below.

Return the number of covered buildings.

Example 1:
Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]
Output: 1
Explanation: Only building [2,2] is covered as it has buildings in all four directions.

Example 2:
Input: n = 3, buildings = [[1,1],[1,2],[2,1],[2,2]]
Output: 0
Explanation: No building has at least one building in all four directions.

Constraints:
- 2 <= n <= 10^5
- 1 <= buildings.length <= 10^5 
- buildings[i] = [x, y]
- 1 <= x, y <= n
- All coordinates of buildings are unique.
```

## Observations

1. **Coverage Definition**: A building at position [x, y] is "covered" if there exists at least one building in each of the four cardinal directions (left, right, above, below).

2. **Coordinate System**: 
   - x represents the row (vertical position)
   - y represents the column (horizontal position)
   - Above means smaller x value, below means larger x value
   - Left means smaller y value, right means larger y value

3. **Key Insight**: Instead of checking every building against every other building (O(n²)), we can preprocess the data:
   - For each horizontal line (same y), track the minimum and maximum x coordinates
   - For each vertical line (same x), track the minimum and maximum y coordinates
   - A building is covered if it's strictly between the min and max in both dimensions

4. **Boundary Buildings**: Buildings at the edges of their row/column cannot be covered since they don't have buildings on both sides.

## Solution

### Approach: Range Tracking with Hash Maps

**Time Complexity**: O(n) where n is the number of buildings  
**Space Complexity**: O(n) for the two hash maps

**Algorithm**:

1. **Preprocessing Phase** - Build two hash maps:
   - `map_hor`: Maps each y-coordinate (column) to [min_x, max_x] - the range of buildings in that column
   - `map_ver`: Maps each x-coordinate (row) to [min_y, max_y] - the range of buildings in that row

2. **Counting Phase** - For each building at [x, y]:
   - **Horizontal coverage**: Check if x is strictly between min_x and max_x for column y
     - This ensures there's a building above (smaller x) and below (larger x)
   - **Vertical coverage**: Check if y is strictly between min_y and max_y for row x
     - This ensures there's a building to the left (smaller y) and right (larger y)
   - Building is covered only if BOTH horizontal and vertical coverage conditions are met

**Example Walkthrough** (Example 1):

Buildings: [[1,2],[2,2],[3,2],[2,1],[2,3]]

After preprocessing:
- `map_hor = {2: [1,3], 1: [2,2], 3: [2,2]}` (column 2 has buildings from row 1 to 3)
- `map_ver = {1: [2,2], 2: [1,3], 3: [2,2]}` (row 2 has buildings from column 1 to 3)

Checking building [2,2]:
- Horizontal: 2 > 1 and 2 < 3 ✓ (has buildings above and below)
- Vertical: 2 > 1 and 2 < 3 ✓ (has buildings left and right)
- Result: Covered!

# Tags
`Array`, `Hash Map`, `Range Query`, `Grid`, `Coordinate Compression`

