## Problem

https://leetcode.com/problems/rectangle-area/description/

Given the coordinates of two rectilinear rectangles in a 2D plane, return the **total area covered by the two rectangles**.

- The first rectangle is defined by its bottom-left corner `(ax1, ay1)` and top-right corner `(ax2, ay2)`.
- The second rectangle is defined by its bottom-left corner `(bx1, by1)` and top-right corner `(bx2, by2)`.

**Example 1:**
```
Input:  ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4,
        bx1 = 0,  by1 = -1, bx2 = 9, by2 = 2
Output: 45
```

**Example 2:**
```
Input:  ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2,
        bx1 = -2, by1 = -2, bx2 = 2, by2 = 2
Output: 16
```

**Constraints:**
- `-10^4 <= ax1 <= ax2 <= 10^4`
- `-10^4 <= ay1 <= ay2 <= 10^4`
- `-10^4 <= bx1 <= bx2 <= 10^4`
- `-10^4 <= by1 <= by2 <= 10^4`

---

## Observations

1. **Simple union of areas** — naively adding `area1 + area2` double-counts the region where the two rectangles overlap. We need to subtract that overlapping region exactly once: `total = area1 + area2 - overlap`.

2. **Overlap is itself a rectangle** — because both shapes are axis-aligned (rectilinear), their intersection (if it exists) is also an axis-aligned rectangle.

3. **Finding the overlapping rectangle** — the overlap on each axis is determined independently:
   - On the **x-axis**: the overlapping segment runs from `max(ax1, bx1)` to `min(ax2, bx2)`.
   - On the **y-axis**: the overlapping segment runs from `max(ay1, by1)` to `min(ay2, by2)`.

4. **Guard against no overlap** — if `left >= right` or `bot >= top`, the rectangles do not intersect (they are disjoint or only touch at an edge), so the overlap area is `0`.

---

## Solution Explanation

```python
class Solution:
    def computeArea(self, ax1: int, ay1: int, ax2: int, ay2: int,
                          bx1: int, by1: int, bx2: int, by2: int) -> int:
        area1 = (ax2 - ax1) * (ay2 - ay1)
        area2 = (bx2 - bx1) * (by2 - by1)

        # common area section
        left  = max(ax1, bx1)
        right = min(ax2, bx2)
        bot   = max(ay1, by1)
        top   = min(ay2, by2)

        common_area = 0
        if left < right and bot < top:
            common_area = (right - left) * (top - bot)

        return area1 + area2 - common_area
```

**Step-by-step:**

1. **Compute individual areas** — straightforward width × height for each rectangle.

2. **Compute the overlapping rectangle's bounds:**
   - `left  = max(ax1, bx1)` — the overlap cannot start before either rectangle begins on the x-axis.
   - `right = min(ax2, bx2)` — the overlap cannot extend past either rectangle ends on the x-axis.
   - `bot   = max(ay1, by1)` — same logic on the y-axis (bottom edge).
   - `top   = min(ay2, by2)` — same logic on the y-axis (top edge).

3. **Check for valid overlap** — only compute `common_area` when `left < right` AND `bot < top`. If either condition fails the rectangles are disjoint in that axis, meaning there is no true 2-D overlap.

4. **Apply inclusion-exclusion** — return `area1 + area2 - common_area`.

**Complexity:**
- **Time:** $O(1)$ — a fixed number of arithmetic and comparison operations.
- **Space:** $O(1)$ — no extra data structures used.
