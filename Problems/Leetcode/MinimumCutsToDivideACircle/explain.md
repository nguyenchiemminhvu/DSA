## Problem

https://leetcode.com/problems/minimum-cuts-to-divide-a-circle/description/

```
A valid cut in a circle can be:
- A cut that is represented by a straight line that touches two points on the edge of the 
  circle and passes through its center (diameter cut), or
- A cut that is represented by a straight line that touches one point on the edge of the 
  circle and its center (radius cut).

Given the integer n, return the minimum number of cuts needed to divide a circle into n 
equal slices.

Example 1:
Input: n = 4
Output: 2
Explanation: The above figure shows how cutting the circle twice through the middle divides 
it into 4 equal slices.

Example 2:
Input: n = 3
Output: 3
Explanation: At least 3 cuts are needed to divide the circle into 3 equal slices. 
It can be shown that less than 3 cuts cannot result in 3 slices of equal size and shape.
Also note that the first cut will not divide the circle into distinct parts.

Constraints:
1 <= n <= 100
```

## Observations

### Key Insights

1. **Special Case - n = 1**: 
   - If we only need 1 slice, the circle is already complete
   - No cuts needed → return 0

2. **Even n (n is divisible by 2)**:
   - For even numbers, we can use **diameter cuts** (cuts through the center touching two edge points)
   - Each diameter cut creates 2 slices
   - For n slices, we need n/2 cuts
   - Examples:
     - n = 2: 1 diameter cut → 2 halves
     - n = 4: 2 diameter cuts → 4 quarter slices
     - n = 6: 3 diameter cuts → 6 slices (each 60°)
     - n = 8: 4 diameter cuts → 8 slices (each 45°)

3. **Odd n (n is not divisible by 2)**:
   - For odd numbers, diameter cuts won't work (we can't divide an odd number by 2)
   - We must use **radius cuts** (cuts from center to one edge point)
   - Each radius cut creates only 1 new slice after the first cut
   - For n slices with odd n, we need n cuts
   - Examples:
     - n = 3: Need 3 radius cuts → 3 slices (each 120°)
     - n = 5: Need 5 radius cuts → 5 slices (each 72°)
     - n = 7: Need 7 radius cuts → 7 slices

### Mathematical Pattern

- **n = 1**: 0 cuts (special case)
- **n is even**: n/2 cuts (using diameter cuts)
- **n is odd** (n > 1): n cuts (using radius cuts)

The key difference: diameter cuts are more efficient (1 cut = 2 slices) but only work for even divisions.

## Solution

1. **Check if n == 1**: 
   - The circle doesn't need to be divided
   - Return 0

2. **Check if n is odd** using `n & 1`:
   - `n & 1` is a bitwise operation that returns 1 if n is odd, 0 if even
   - For odd n, we can't use diameter cuts efficiently
   - Return n (need n radius cuts)

3. **For even n**:
   - Use diameter cuts which create 2 slices per cut
   - Return n // 2 (integer division)

### Complexity Analysis

- **Time Complexity**: O(1) - Only constant time operations (comparisons and arithmetic)
- **Space Complexity**: O(1) - No additional space used

### Why This Works

**Geometric reasoning**:
- Equal slices in a circle mean equal angles from the center
- For n slices: each slice has angle = 360°/n

**Even n**:
- Angle = 360°/n
- Each diameter cut creates 2 opposite slices
- n/2 diameter cuts at angles: 0°, 360°/n, 2×360°/n, ..., ((n/2)-1)×360°/n

**Odd n**:
- Can't pair slices symmetrically with diameter cuts
- Must use radius cuts from center to edge
- n radius cuts at angles: 0°, 360°/n, 2×360°/n, ..., (n-1)×360°/n

# Tags

`Math` `Geometry` `Pattern Recognition` `Easy`

