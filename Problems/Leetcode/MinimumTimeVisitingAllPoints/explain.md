## Problem

https://leetcode.com/problems/minimum-time-visiting-all-points/description/

```
On a 2D plane, there are n points with integer coordinates points[i] = [xi, yi]. Return the minimum time in seconds to visit all the points in the order given by points.

You can move according to these rules:

In 1 second, you can either:
move vertically by one unit,
move horizontally by one unit, or
move diagonally sqrt(2) units (in other words, move one unit vertically then one unit horizontally in 1 second).
You have to visit the points in the same order as they appear in the array.
You are allowed to pass through points that appear later in the order, but these do not count as visits.

Example 1:

Input: points = [[1,1],[3,4],[-1,0]]
Output: 7
Explanation: One optimal path is [1,1] -> [2,2] -> [3,3] -> [3,4] -> [2,3] -> [1,2] -> [0,1] -> [-1,0]   
Time from [1,1] to [3,4] = 3 seconds 
Time from [3,4] to [-1,0] = 4 seconds
Total time = 7 seconds

Example 2:

Input: points = [[3,2],[-2,2]]
Output: 5

Constraints:

points.length == n
1 <= n <= 100
points[i].length == 2
-1000 <= points[i][0], points[i][1] <= 1000
```

## Observations

1. **Movement Rules**: We can move in three ways each second:
   - Horizontally by 1 unit: `(x, y) -> (x±1, y)`
   - Vertically by 1 unit: `(x, y) -> (x, y±1)` 
   - Diagonally by √2 units: `(x, y) -> (x±1, y±1)`

2. **Key Insight - Chebyshev Distance**: Since diagonal movement covers both horizontal and vertical distance simultaneously, the minimum time between two points is actually the **Chebyshev distance** (also called L∞ distance or chessboard distance).

3. **Chebyshev Distance Formula**: For points `(x1, y1)` and `(x2, y2)`:
   ```
   distance = max(|x2 - x1|, |y2 - y1|)
   ```

4. **Why Maximum Instead of Sum**: 
   - If we need to move `dx = |x2 - x1|` horizontally and `dy = |y2 - y1|` vertically
   - We can move diagonally for `min(dx, dy)` steps, covering both axes simultaneously
   - Then move in straight line for `|dx - dy|` steps to cover the remaining distance
   - Total time = `min(dx, dy) + |dx - dy| = max(dx, dy)`

5. **Movement Strategy Example**: From `(1,1)` to `(4,3)`:
   - `dx = 3, dy = 2`
   - Move diagonally 2 steps: `(1,1) -> (2,2) -> (3,3)`
   - Move horizontally 1 step: `(3,3) -> (4,3)`
   - Total time: `max(3, 2) = 3` seconds

6. **Sequential Processing**: Since we must visit points in order, we calculate the time between each consecutive pair and sum them up.

## Solution

### Approach: Chebyshev Distance Calculation

The solution leverages the mathematical insight that the minimum time between two points under the given movement rules is the Chebyshev distance.

**Algorithm:**
1. Define a helper function `distance(p1, p2)` that calculates Chebyshev distance
2. Iterate through consecutive point pairs in the array
3. Sum up all the distances to get total minimum time

**Step-by-Step Execution for Example 1:**
- Points: `[[1,1],[3,4],[-1,0]]`
- From `[1,1]` to `[3,4]`: `max(|3-1|, |4-1|) = max(2, 3) = 3`
- From `[3,4]` to `[-1,0]`: `max(|-1-3|, |0-4|) = max(4, 4) = 4`
- Total: `3 + 4 = 7` seconds

**Time Complexity**: O(n) where n is the number of points
**Space Complexity**: O(1) - only using constant extra space

# Tags

`Array` `Math` `Geometry` `Chebyshev Distance` `Greedy`

