## Problem

https://leetcode.com/problems/rectangle-overlap/description/

An axis-aligned rectangle is represented as a list `[x1, y1, x2, y2]`, where `(x1, y1)` is the coordinate of its bottom-left corner, and `(x2, y2)` is the coordinate of its top-right corner. Its top and bottom edges are parallel to the X-axis, and its left and right edges are parallel to the Y-axis.

Two rectangles overlap if the area of their intersection is positive. To be clear, two rectangles that only touch at the corner or edges do not overlap.

Given two axis-aligned rectangles `rec1` and `rec2`, return `true` if they overlap, otherwise return `false`.

**Example 1:**
```
Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
Output: true
```

**Example 2:**
```
Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
Output: false
```

**Example 3:**
```
Input: rec1 = [0,0,1,1], rec2 = [2,2,3,3]
Output: false
```

**Constraints:**
- `rec1.length == 4`
- `rec2.length == 4`
- `-10^9 <= rec1[i], rec2[i] <= 10^9`
- `rec1` and `rec2` represent a valid rectangle with a non-zero area.

## Observations

1. **Rectangle Representation**: Each rectangle is defined by two points: bottom-left `(x1, y1)` and top-right `(x2, y2)`.

2. **Overlap Definition**: Two rectangles overlap if their intersection has a positive area. Touching at edges or corners doesn't count as overlap.

3. **Non-Overlap Conditions**: Two rectangles DON'T overlap if:
   - One rectangle is completely to the left of the other
   - One rectangle is completely to the right of the other
   - One rectangle is completely above the other
   - One rectangle is completely below the other

4. **Key Insight**: It's easier to check for non-overlap conditions and negate the result, rather than checking all overlap conditions directly.

5. **Sorting Strategy**: The solution sorts rectangles by their bottom-left corner coordinates to establish a consistent reference frame, though this isn't strictly necessary for the algorithm to work.

6. **Boundary Cases**: 
   - When rectangles share an edge (e.g., `x2 == xx1`), they don't overlap (area = 0)
   - When rectangles share only a corner point, they don't overlap

## Solution

### Approach: Check Non-Overlap Conditions

The algorithm uses the principle that it's simpler to detect when rectangles DON'T overlap:

**Step 1: Sort Rectangles**
- Sort the two rectangles by their bottom-left corner coordinates `(x1, y1)`
- This establishes `rect1` as the "reference" rectangle (leftmost, or bottom-most if x-coordinates are equal)

**Step 2: Extract Coordinates**
- `rect1`: `(x1, y1)` to `(x2, y2)`
- `rect2`: `(xx1, yy1)` to `(xx2, yy2)`

**Step 3: Check Non-Overlap Conditions**

Three conditions where rectangles DON'T overlap:

1. **`x2 <= xx1`**: `rect1` is completely to the left of `rect2`
   - The right edge of `rect1` is at or before the left edge of `rect2`

2. **`y2 <= yy1`**: `rect1` is completely below `rect2`
   - The top edge of `rect1` is at or below the bottom edge of `rect2`

3. **`y1 >= yy2`**: `rect1` is completely above `rect2`
   - The bottom edge of `rect1` is at or above the top edge of `rect2`

If ANY of these conditions is true, the rectangles don't overlap.

**Step 4: Return Result**
- If none of the non-overlap conditions are met, the rectangles must overlap

### Code Implementation

```python
class Solution:
    def isRectangleOverlap(self, rec1: List[int], rec2: List[int]) -> bool:
        # Sort rectangles by bottom-left corner (x1, y1)
        rects = [rec1, rec2]
        rects.sort(key=lambda x: (x[0], x[1]))
        rect1, rect2 = rects[0], rects[1]
        
        # Extract coordinates
        x1, y1, x2, y2 = rect1
        xx1, yy1, xx2, yy2 = rect2
        
        # Check non-overlap conditions
        if x2 <= xx1 or y2 <= yy1 or y1 >= yy2:
            return False
        
        return True
```

### Complexity Analysis

- **Time Complexity**: $O(1)$
  - Sorting 2 elements is constant time
  - All comparisons are constant time operations
  
- **Space Complexity**: $O(1)$
  - Only using a fixed amount of extra space for the sorted list and variables

### Alternative Simpler Approach

The sorting step is actually unnecessary. We can directly check non-overlap conditions:

```python
class Solution:
    def isRectangleOverlap(self, rec1: List[int], rec2: List[int]) -> bool:
        x1, y1, x2, y2 = rec1
        xx1, yy1, xx2, yy2 = rec2
        
        # Check if one rectangle is to the left, right, above, or below the other
        if x2 <= xx1 or xx2 <= x1 or y2 <= yy1 or yy2 <= y1:
            return False
        
        return True
```

This checks all four possible non-overlap scenarios:
- `x2 <= xx1`: rec1 is completely left of rec2
- `xx2 <= x1`: rec2 is completely left of rec1
- `y2 <= yy1`: rec1 is completely below rec2
- `yy2 <= y1`: rec2 is completely below rec1

# Tags

`Math` `Geometry` `Rectangle Intersection`

