## Problem

https://leetcode.com/problems/max-points-on-a-line/description/

Given an array of `points` where `points[i] = [xi, yi]` represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.

**Examples:**
- `[[1,1],[2,2],[3,3]]` → `3` (all three points are colinear on `y = x`)
- `[[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]` → `4`

**Constraints:** `1 <= points.length <= 300`, `-10^4 <= xi, yi <= 10^4`, all points are unique.

## Observations

1. **A line through two distinct points is uniquely determined.** Fix one point as a "pivot" and look at every other point relative to it — points lying on the same line through the pivot all share the same direction (i.e., the same slope).

2. **Slope is the natural fingerprint of a line through a fixed pivot.** For pivot $(x, y)$ and another point $(x', y')$:
   $$\text{slope} = \frac{y' - y}{x' - x}$$
   Two points share a line through the pivot iff they have the same slope relative to it.

3. **Vertical lines need a sentinel.** When `x' == x`, the slope is undefined (division by zero). We treat it as `INF` so vertical lines bucket together correctly.

4. **The answer must include the pivot itself.** If `k` other points share a slope with the pivot, the line contains `k + 1` points (the pivot plus those `k`).

5. **Pivot rotation covers every possible line.** Iterating the pivot over all `n` points and grouping the remaining `n - 1` by slope guarantees we examine every line that passes through at least two points. Any line with the maximum count is found when we pivot on any point on it.

6. **Trivial bound.** With `n >= 1`, at least one point is always on "a line", so the result is at least `1`.

7. **Constraint sizing.** `n <= 300` makes $O(n^2)$ comfortably fast. Coordinates are bounded by `10^4`, so floating-point slopes are usually fine here — though for exact correctness in the general case one would store slopes as reduced `(dy, dx)` pairs via `gcd`.

## Solution

### Approach — Pivot + Slope Bucketing

For each pivot point `(x, y)`, count how many other points share each slope to it. The largest bucket plus one (for the pivot itself) is the maximum number of colinear points through that pivot. The global answer is the maximum over all pivots.

**State.** `mp[(x, y)][slope]` = number of points (other than the pivot) that lie on the line through pivot `(x, y)` with the given `slope`.

**Slope helper.**
```python
def cal_slope(x1, y1, x2, y2):
    if x1 == x2:
        return INF        # vertical line sentinel
    return (y2 - y1) / (x2 - x1)
```

**Main loop.** For every ordered pair `(i, j)` with `i != j`, compute the slope from point `i` to point `j` and increment `mp[(xi, yi)][slope]`.

```python
for i in range(n):
    x, y = points[i]
    for j in range(n):
        if j == i:
            continue
        x1, y1 = points[j]
        slope = cal_slope(x, y, x1, y1)
        mp[(x, y)][slope] += 1
```

**Answer.** For each pivot and each slope bucket, the line contains `count + 1` points (count of others + the pivot). Take the global max, with a floor of `1` to handle the `n == 1` edge case.

```python
res = 1
for (x, y) in mp.keys():
    for slope in mp[(x, y)]:
        res = max(res, mp[(x, y)][slope] + 1)
return res
```

**Walk-through on `[[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]`:**

Pivot at `(1, 1)` (index 0). Slopes to the other 5 points:

| target | dy/dx | slope |
|--------|-------|-------|
| (3,2)  | 1/2   | 0.5   |
| (5,3)  | 2/4   | 0.5   |
| (4,1)  | 0/3   | 0.0   |
| (2,3)  | 2/1   | 2.0   |
| (1,4)  | 3/0   | INF   |

Bucket counts at pivot `(1,1)`: `{0.5: 2, 0.0: 1, 2.0: 1, INF: 1}` → best is `2 + 1 = 3`.

Pivot at `(3, 2)` (index 1). Slopes:

| target | dy/dx  | slope |
|--------|--------|-------|
| (1,1)  | -1/-2  | 0.5   |
| (5,3)  | 1/2    | 0.5   |
| (4,1)  | -1/1   | -1.0  |
| (2,3)  | 1/-1   | -1.0  |
| (1,4)  | 2/-2   | -1.0  |

Bucket counts: `{0.5: 2, -1.0: 3}` → best is `3 + 1 = 4`. **This is the answer.**

The line `y = -x + 5` passes through `(3,2), (4,1), (2,3), (1,4)` — four points. ✓

**Why iterate `j` over all indices (not just `j > i`)?**
The code uses an asymmetric layout: each pivot keeps its own bucket map, so we count *neighbors of this pivot* by visiting every other index. Using `j > i` would undercount because, e.g., pivot `(3,2)` would never see `(1,1)`. A symmetric variant (only `j > i`) is possible but then you must increment buckets at *both* endpoints — the code here picks the simpler asymmetric form at the cost of doing each pair twice.

**Complexity:**
- Time: $O(n^2)$ — every ordered pair is visited once.
- Space: $O(n^2)$ in the worst case — each of the `n` pivots can have up to `n - 1` distinct slopes.

### Notes / Caveats

- **Floating-point slopes** can collide or differ for mathematically equal slopes due to rounding. Within the given coordinate range (`|xi|, |yi| <= 10^4`) this passes, but the robust form keys on a normalized `(dy, dx)` pair reduced by `gcd`, with sign canonicalized.
- **`n == 1` edge case** is handled by initializing `res = 1`; the inner loop never executes, so `mp` stays empty.
- **Duplicate points** are excluded by the problem ("all points are unique"), so we don't need to handle the "same-point" bucket separately.

```python
class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        mp = defaultdict(lambda: defaultdict(int))  # mp[(x, y)][slope] -> count of points through (x, y) with that slope

        INF = float('inf')
        def cal_slope(x1, y1, x2, y2):
            if x1 == x2:
                return INF
            return (y2 - y1) / (x2 - x1)

        n = len(points)
        for i in range(n):
            x, y = points[i]
            for j in range(n):
                if j == i:
                    continue
                x1, y1 = points[j]
                slope = cal_slope(x, y, x1, y1)
                mp[(x, y)][slope] += 1

        res = 1
        for (x, y) in mp.keys():
            for slope in mp[(x, y)]:
                res = max(res, mp[(x, y)][slope] + 1)
        return res
```
