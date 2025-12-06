## Problem

https://leetcode.com/problems/check-if-it-is-a-straight-line/description/

You are given an integer array `coordinates`, where `coordinates[i] = [x, y]` represents the coordinate of a point. Check if these points make a straight line in the XY plane.

**Example 1:**
```
Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
Output: true
```

**Example 2:**
```
Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
Output: false
```

**Constraints:**
- `2 <= coordinates.length <= 1000`
- `coordinates[i].length == 2`
- `-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4`
- `coordinates` contains no duplicate point

## Observations

1. **Slope Consistency**: For all points to lie on a straight line, the slope between any two points must be the same as the slope between the first two points.

2. **Slope Formula**: The slope between two points $(x_1, y_1)$ and $(x_2, y_2)$ is:
   $$\text{slope} = \frac{y_2 - y_1}{x_2 - x_1}$$

3. **Special Cases**:
   - If there are only 2 points, they always form a straight line
   - Vertical lines have undefined slope (division by zero when $x_2 - x_1 = 0$)
   - Horizontal lines have slope = 0

4. **Floating Point Precision**: Using division to calculate slopes can lead to floating-point precision issues. A better approach is to use cross-multiplication to avoid division.

5. **Alternative Approach**: Instead of calculating slopes directly, we can use the property that for three points to be collinear:
   $$(y_2 - y_1) \times (x_3 - x_1) = (y_3 - y_1) \times (x_2 - x_1)$$
   This avoids division and floating-point errors.

## Solution

### Approach 1: Slope Comparison (Provided Solution)

**Algorithm:**
1. If there are only 2 points, return `True` immediately
2. Sort coordinates by x-coordinate first, then y-coordinate
3. Calculate the slope between the first two points as reference
4. For each subsequent point, calculate its slope with the first point
5. If any slope differs from the reference slope, return `False`
6. If all slopes match, return `True`

**Time Complexity:** $O(n \log n)$ due to sorting  
**Space Complexity:** $O(1)$ if we don't count the sorting space

**Issues with this approach:**
- The function is misnamed as `dot_product` when it actually calculates slope
- Sorting is unnecessary since we're checking all points against the first point
- Floating-point comparison can be problematic
- Using `float('inf')` for vertical lines works but is not the cleanest approach

### Approach 2: Cross-Multiplication (Optimized)

**Algorithm:**
1. Use the first point as reference
2. Calculate the slope components (dx, dy) between the first and second points
3. For each subsequent point, use cross-multiplication to check collinearity
4. Formula: `(y - y0) * dx == (x - x0) * dy`

**Time Complexity:** $O(n)$ - single pass through coordinates  
**Space Complexity:** $O(1)$ - only using constant extra space

**Advantages:**
- No division, avoiding floating-point precision issues
- No sorting needed
- Handles vertical and horizontal lines naturally
- Cleaner and more efficient

# Tags
`Array` `Math` `Geometry` `Slope` `Collinearity`

