## Problem

https://leetcode.com/problems/circle-and-rectangle-overlapping/description/

You are given a circle represented as `(radius, xCenter, yCenter)` and an axis-aligned rectangle represented as `(x1, y1, x2, y2)`, where `(x1, y1)` are the coordinates of the bottom-left corner, and `(x2, y2)` are the coordinates of the top-right corner of the rectangle.

Return `true` if the circle and rectangle are overlapped, otherwise return `false`. In other words, check if there is **any** point `(xi, yi)` that belongs to the circle and the rectangle at the same time.

**Example 1:**
```
Input: radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
Output: true
Explanation: Circle and rectangle share the point (1, 0).
```

**Example 2:**
```
Input: radius = 1, xCenter = 1, yCenter = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1
Output: false
```

**Example 3:**
```
Input: radius = 1, xCenter = 0, yCenter = 0, x1 = -1, y1 = 0, x2 = 0, y2 = 1
Output: true
```

**Constraints:**
- `1 <= radius <= 2000`
- `-10^4 <= xCenter, yCenter <= 10^4`
- `-10^4 <= x1 < x2 <= 10^4`
- `-10^4 <= y1 < y2 <= 10^4`

## Observations

1. **Circle vs. Rectangle Overlap**: The circle (a closed disk) and the (filled) rectangle overlap iff they share at least one common point. Touching at a single point counts as overlap.

2. **Geometric Reformulation**: The disk is the set of points within distance `radius` from `(xCenter, yCenter)`. The two regions overlap iff the distance from the center to the (filled) rectangle is `<= radius`, where this distance is `0` when the center is inside the rectangle and is the distance to the nearest boundary point otherwise.

3. **Two Cases to Consider**:
   - **Case A — Center inside rectangle**: `(xCenter, yCenter)` lies in `[x1, x2] x [y1, y2]`. Then the center itself is shared by both shapes, so they overlap regardless of `radius`.
   - **Case B — Center outside rectangle**: The closest point of the rectangle to the center lies on its boundary, i.e., on one of the 4 edges. The shapes overlap iff the minimum distance from the center to any of the 4 edges is `<= radius`.

4. **Why Edges (Segments), Not Just Corners**: If we only measured distance to the 4 corners, we would miss cases where the closest point is on the interior of an edge (e.g., a circle just below the bottom edge whose closest rectangle point is directly above the center on that edge).

5. **Point-to-Segment Distance**: For each edge `P1 -> P2` of the rectangle, the closest point to `(x0, y0)` is found by projecting onto the line through `P1, P2` and clamping the projection parameter `t` to `[0, 1]`:
   - If `t < 0`, closest point is `P1`.
   - If `t > 1`, closest point is `P2`.
   - Else, closest point is `P1 + t * (P2 - P1)`.

   This handles both the "perpendicular foot lies on edge" and the "corner is closest" cases in one formula.

6. **Numerical Note**: All inputs are integers and the closed-disk overlap condition includes equality (`<= radius`), so floating-point comparisons are safe within the given constraints. Squared distances would avoid the square root entirely if stricter precision were needed.

## Solution

### Approach: Minimum Distance From Center to Rectangle

Reduce overlap testing to a single geometric question: *what is the minimum distance from the circle's center to the rectangle?* The shapes overlap iff that distance is `<= radius`, OR the center already lies inside the rectangle.

**Step 1: Helper — Point-to-Segment Distance**

For a segment from `(sx1, sy1)` to `(sx2, sy2)` and a query point `(x0, y0)`:

- Compute the direction vector `(dx, dy) = (sx2 - sx1, sy2 - sy1)`.
- Degenerate case `dx == dy == 0` (segment is a point): return Euclidean distance to that point.
- Otherwise compute the projection parameter:

   $$ t = \frac{(x_0 - sx_1)\,dx + (y_0 - sy_1)\,dy}{dx^2 + dy^2} $$

- Clamp `t` to `[0, 1]` so the closest point stays on the segment.
- The closest point is `(sx1 + t*dx, sy1 + t*dy)`; return its Euclidean distance to `(x0, y0)`.

**Step 2: Distance to Each of the 4 Rectangle Edges**

The axis-aligned rectangle has 4 edges:

| Edge   | From         | To           |
|--------|--------------|--------------|
| Bottom | `(x1, y1)`   | `(x2, y1)`   |
| Top    | `(x1, y2)`   | `(x2, y2)`   |
| Left   | `(x1, y1)`   | `(x1, y2)`   |
| Right  | `(x2, y1)`   | `(x2, y2)`   |

Apply the helper to each edge against `(xCenter, yCenter)`.

**Step 3: Combine**

- `min_dist` = minimum of the 4 edge distances → distance from the center to the rectangle's boundary.
- `is_inside` = whether `(xCenter, yCenter)` lies in `[x1, x2] x [y1, y2]`.
- Return `min_dist <= radius OR is_inside`.

The `is_inside` branch is the safety net for **Case A**: when the center is strictly inside the rectangle, the boundary may still be farther than `radius` (e.g., a tiny circle deep inside a huge rectangle), but the shapes obviously overlap because the center itself is a shared point.

### Code Implementation

```python
class Solution:
    def checkOverlap(self, radius: int, xCenter: int, yCenter: int,
                     x1: int, y1: int, x2: int, y2: int) -> bool:

        # Helper: minimum distance from (x0, y0) to segment (sx1, sy1)-(sx2, sy2)
        def point_to_segment_dist(x0, y0, sx1, sy1, sx2, sy2):
            dx, dy = sx2 - sx1, sy2 - sy1
            if dx == 0 and dy == 0:
                return ((x0 - sx1) ** 2 + (y0 - sy1) ** 2) ** 0.5

            # Projection factor t, clamped to [0, 1] to stay on the segment
            t = ((x0 - sx1) * dx + (y0 - sy1) * dy) / (dx * dx + dy * dy)
            t = max(0, min(1, t))

            xc = sx1 + t * dx
            yc = sy1 + t * dy
            return ((x0 - xc) ** 2 + (y0 - yc) ** 2) ** 0.5

        # 1. Distance from center to each of the 4 rectangle edges
        bottom = point_to_segment_dist(xCenter, yCenter, x1, y1, x2, y1)
        top    = point_to_segment_dist(xCenter, yCenter, x1, y2, x2, y2)
        left   = point_to_segment_dist(xCenter, yCenter, x1, y1, x1, y2)
        right  = point_to_segment_dist(xCenter, yCenter, x2, y1, x2, y2)

        # 2. Minimum distance to the rectangle's boundary
        min_dist = min(bottom, top, left, right)

        # 3. Center inside (or on the boundary of) the rectangle
        is_inside = (x1 <= xCenter <= x2) and (y1 <= yCenter <= y2)

        # Overlap iff the boundary is within reach OR the center is inside
        return min_dist <= radius or is_inside
```

### Complexity

- **Time**: `O(1)` — constant work: 4 segment-distance computations.
- **Space**: `O(1)` — only a few scalar variables.

### Alternative: Clamp-Based One-Liner

A simpler equivalent approach avoids segment math entirely by noting that the closest point of an axis-aligned rectangle to `(xCenter, yCenter)` is just the center clamped into the rectangle's range:

```python
cx = max(x1, min(xCenter, x2))
cy = max(y1, min(yCenter, y2))
return (xCenter - cx) ** 2 + (yCenter - cy) ** 2 <= radius * radius
```

- If the center is inside the rectangle, `(cx, cy) == (xCenter, yCenter)`, so the squared distance is `0` and the test trivially passes — naturally handling Case A without a separate `is_inside` check.
- Uses squared distances, avoiding the square root and any floating-point error.
