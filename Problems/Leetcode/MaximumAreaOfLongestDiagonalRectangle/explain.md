## Problem

https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/

```
You are given a 2D 0-indexed integer array dimensions.

For all indices i, 0 <= i < dimensions.length, dimensions[i][0] represents the length and dimensions[i][1] represents the width of the rectangle i.

Return the area of the rectangle having the longest diagonal. If there are multiple rectangles with the longest diagonal, return the area of the rectangle having the maximum area.

Example 1:
Input: dimensions = [[9,3],[8,6]]
Output: 48
Explanation: 
For index = 0, length = 9 and width = 3. Diagonal length = sqrt(9 * 9 + 3 * 3) = sqrt(90) ≈ 9.487.
For index = 1, length = 8 and width = 6. Diagonal length = sqrt(8 * 8 + 6 * 6) = sqrt(100) = 10.
So, the rectangle at index 1 has a greater diagonal length therefore we return area = 8 * 6 = 48.

Example 2:
Input: dimensions = [[3,4],[4,3]]
Output: 12
Explanation: Length of diagonal is the same for both which is 5, so maximum area = 12.

Constraints:
- 1 <= dimensions.length <= 100
- dimensions[i].length == 2
- 1 <= dimensions[i][0], dimensions[i][1] <= 100
```

## Observations

1. **Diagonal Calculation**: For a rectangle with length $l$ and width $w$, the diagonal length is calculated using the Pythagorean theorem: $d = \sqrt{l^2 + w^2}$

2. **Primary Goal**: Find the rectangle with the longest diagonal

3. **Tiebreaker**: If multiple rectangles have the same longest diagonal, return the one with the maximum area

4. **Key Insight**: We can optimize by sorting rectangles by diagonal length (descending) and then only checking rectangles with the maximum diagonal length

5. **Area Calculation**: Area = length × width

## Solution

### Approach: Sort by Diagonal + Linear Scan

**Algorithm:**
1. Sort the array in descending order by diagonal length
2. Calculate the longest diagonal (from the first element after sorting)
3. Iterate through sorted rectangles and find maximum area among those with the longest diagonal
4. Stop early when we encounter a rectangle with a shorter diagonal

**Time Complexity:** $O(n \log n)$ where $n$ is the number of rectangles (dominated by sorting)

**Space Complexity:** $O(1)$ excluding the space used for sorting (in-place sort uses $O(\log n)$ stack space)

Input: `dimensions = [[9,3],[8,6]]`

1. Calculate diagonals:
   - Rectangle 0: $\sqrt{9^2 + 3^2} = \sqrt{90} \approx 9.487$
   - Rectangle 1: $\sqrt{8^2 + 6^2} = \sqrt{100} = 10$

2. After sorting by diagonal (descending): `[[8,6], [9,3]]`

3. Longest diagonal: 10

4. Iterate:
   - `[8,6]`: diagonal = 10, area = 48, res = 48
   - `[9,3]`: diagonal ≈ 9.487 < 10, break

5. Return 48

**Optimization Note:** The alternative single-pass approach is more efficient with $O(n)$ time complexity and avoids the sorting overhead. It also avoids repeated `sqrt()` calculations by comparing squared diagonals.

# Tags

`Array` `Math` `Sorting` `Geometry`

