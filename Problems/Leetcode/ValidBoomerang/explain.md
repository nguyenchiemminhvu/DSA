## Problem

https://leetcode.com/problems/valid-boomerang/description/

```
Given an array points where points[i] = [xi, yi] represents a point on the X-Y plane, return true if these points are a boomerang.

A boomerang is a set of three points that are all distinct and not in a straight line.

Example 1:

Input: points = [[1,1],[2,3],[3,2]]
Output: true

Example 2:

Input: points = [[1,1],[2,2],[3,3]]
Output: false

Constraints:

points.length == 3
points[i].length == 2
0 <= xi, yi <= 100
```

## Observations

1. **Problem Understanding**: A boomerang is valid if three points are:
   - All distinct (no two points are the same)
   - Not collinear (not on the same straight line)

2. **Key Insights**:
   - If any two points are identical, it's not a valid boomerang
   - Three points are collinear if they have the same slope between any two pairs
   - We need to handle vertical lines (undefined slope) carefully

3. **Edge Cases to Consider**:
   - Duplicate points: `[[1,1],[1,1],[2,3]]`
   - Vertical lines: `[[1,1],[1,2],[1,3]]` (all x-coordinates same)
   - Mixed vertical/non-vertical: `[[1,1],[1,2],[2,3]]`
   - Collinear points: `[[1,1],[2,2],[3,3]]`

4. **Mathematical Approach**:
   - For non-vertical lines: Use slope formula `m = (y2-y1)/(x2-x1)`
   - For vertical lines: Check if x-coordinates are equal
   - Points are collinear if slopes between point pairs are equal

## Solution

The solution uses a slope-based approach with careful handling of vertical lines:

### Algorithm Steps:

1. **Check for duplicate points**: If any two points are identical, return `False`

2. **Handle vertical line cases**:
   - If both line segments are vertical (same x-coordinates), points are collinear → return `False`
   - If only one segment is vertical, points cannot be collinear → return `True`

3. **Calculate slopes for non-vertical cases**:
   - Compute slope between points 1-2: `m1 = (y2-y1)/(x2-x1)`
   - Compute slope between points 2-3: `m2 = (y3-y2)/(x3-x2)`
   - If slopes are different, points form a valid boomerang → return `True`

### Code Analysis:

```python
class Solution:
    def isBoomerang(self, p: List[List[int]]) -> bool:
        # Check for duplicate points
        if p[0] == p[1] or p[1] == p[2]:
            return False

        x1, y1 = p[0]
        x2, y2 = p[1]
        x3, y3 = p[2]

        # Handle vertical line cases
        if (x2 == x1) and (x3 == x2):  # Both segments vertical
            return False
        if ((x2 == x1) and (x3 != x2)) or ((x2 != x1) and (x3 == x2)):  # Only one vertical
            return True

        # Calculate slopes and compare
        m1 = (y2 - y1) / (x2 - x1)
        m2 = (y3 - y2) / (x3 - x2)
        return m1 != m2
```

### Time & Space Complexity:
- **Time**: O(1) - Constant time operations
- **Space**: O(1) - Only using a few variables

### Alternative Approach (Cross Product):
A more elegant solution uses the cross product to avoid division:
```python
def isBoomerang(self, points):
    (x1, y1), (x2, y2), (x3, y3) = points
    return (y2 - y1) * (x3 - x2) != (y3 - y2) * (x2 - x1)
```

This works because points are collinear if and only if the cross product is zero.

# Tags

`Math` `Geometry` `Slope` `Collinear Points`

