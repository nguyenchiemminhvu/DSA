## Problem

https://leetcode.com/problems/generate-random-point-in-a-circle/description/

Given the radius and the position of the center of a circle, implement the function `randPoint` which generates a **uniform random point inside the circle**.

A point on the circumference of the circle is also considered to be inside the circle.

---

## Observations

1. **Naive approach — rejection sampling**: Generate a random point `(x, y)` inside the bounding square `[x_center - r, x_center + r] × [y_center - r, y_center + r]`, then reject it if it falls outside the circle. This works but is inefficient (~21.5% of points are rejected on average).

2. **Why not just pick a random radius and angle?** The intuitive approach of choosing:
   - `r = radius * random()` (uniform in `[0, radius]`)
   - `theta = 2π * random()`

   ...produces a **non-uniform** distribution. Points cluster near the center because inner rings have less area than outer rings, but both get the same probability of being picked.

3. **Correct approach — square-root trick**: To achieve uniform distribution over the disk, we must account for the fact that area grows as $r^2$. The area of an annular ring at radius $r$ with width $dr$ is $dA = 2\pi r \, dr$, so the CDF of the radial distance is:

$$F(r) = \frac{r^2}{R^2}$$

   Applying the **inverse transform sampling** method: if $u$ is uniform in $[0, 1]$, then $r = R\sqrt{u}$ gives a radially uniform distribution. This ensures the probability of landing in any region is proportional to that region's **area**.

---

## Solution

```python
import math
import random
from typing import List

class Solution:

    def __init__(self, radius: float, x_center: float, y_center: float):
        self.x = x_center
        self.y = y_center
        self.r = radius

    def randPoint(self) -> List[float]:
        # Sample a radius proportional to sqrt(uniform) to get uniform area distribution
        r = self.r * sqrt(random.random())
        # Sample a uniformly random angle in [0, 2π)
        theta = 2 * math.pi * random.random()
        # Convert polar coordinates (r, theta) to Cartesian (x, y)
        x = self.x + math.cos(theta) * r
        y = self.y + math.sin(theta) * r
        return [x, y]
```

### Step-by-step explanation

| Step | Expression | Purpose |
|------|-----------|---------|
| 1 | `r = R * sqrt(random())` | Corrects for non-uniform radial density — inner circles have less area |
| 2 | `theta = 2π * random()` | Uniform angle covering the full circle |
| 3 | `x = x_center + cos(θ) * r` | Convert polar → Cartesian x-coordinate |
| 4 | `y = y_center + sin(θ) * r` | Convert polar → Cartesian y-coordinate |

### Why `sqrt(random())`?

The area of a disk of radius $r$ is $\pi r^2$. To sample points uniformly by area, the CDF of the radial component must be:

$$F(r) = \frac{\pi r^2}{\pi R^2} = \frac{r^2}{R^2}$$

Inverting: $r = R\sqrt{u}$ where $u \sim \text{Uniform}(0, 1)$.

Without the `sqrt`, the density would be **uniform in radius** (not area), causing the center region to be **over-sampled**.

---

## Complexity

- **Time**: $O(1)$ per `randPoint()` call
- **Space**: $O(1)$
