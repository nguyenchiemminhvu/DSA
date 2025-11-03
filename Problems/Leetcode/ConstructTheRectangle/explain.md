## Problem

https://leetcode.com/problems/construct-the-rectangle/

```
A web developer needs to know how to design a web page's size. So, given a specific rectangular web page’s area, your job by now is to design a rectangular web page, whose length L and width W satisfy the following requirements:

The area of the rectangular web page you designed must equal to the given target area.
The width W should not be larger than the length L, which means L >= W.
The difference between length L and width W should be as small as possible.
Return an array [L, W] where L and W are the length and width of the web page you designed in sequence.

Example 1:

Input: area = 4
Output: [2,2]
Explanation: The target area is 4, and all the possible ways to construct it are [1,4], [2,2], [4,1]. 
But according to requirement 2, [1,4] is illegal; according to requirement 3,  [4,1] is not optimal compared to [2,2]. So the length L is 2, and the width W is 2.

Example 2:

Input: area = 37
Output: [37,1]

Example 3:

Input: area = 122122
Output: [427,286]

Constraints:

1 <= area <= 107
```

## Observations

1. **Problem Understanding**: We need to find two factors L and W of the given area such that:
   - L × W = area
   - L ≥ W (length should be greater than or equal to width)
   - L - W should be minimized (closest to a square shape)

2. **Mathematical Insight**: To minimize L - W, we want L and W to be as close as possible to √area. The optimal solution occurs when we find the largest width W ≤ √area that divides the area evenly.

3. **Brute Force vs Optimized**: 
   - Brute force: Check all numbers from 1 to area to find divisors
   - Optimized: Only check numbers from 1 to √area since divisors come in pairs

4. **Key Insight**: If we iterate through potential widths from √area down to 1, the first valid divisor we find will give us the optimal rectangle (closest to square).

## Solution

### Approach 1: Find All Divisors (Given Solution)
The provided solution finds all divisors first, then selects the optimal pair.

**Algorithm:**
1. Find all divisors of the area using the `get_divisors` helper function
2. Sort the divisors in ascending order
3. Iterate through divisors as potential widths, calculate corresponding length
4. Track the pair with minimum difference between length and width

**Time Complexity:** O(√n + d log d) where d is the number of divisors
**Space Complexity:** O(d) to store all divisors

**Issues with the current implementation:**
- The `get_divisors` function has a bug: it should include the square root if it's a perfect square
- The range should be `range(1, sqrt + 1)` instead of `range(1, sqrt)`

### Approach 2: Optimized Direct Search (Better)
```python
def constructRectangle(self, area: int) -> List[int]:
    width = int(math.sqrt(area))
    while area % width != 0:
        width -= 1
    return [area // width, width]
```

**Algorithm:**
1. Start with width = √area (rounded down)
2. Decrease width until we find a divisor of area
3. Return [area // width, width]

**Time Complexity:** O(√n) in worst case
**Space Complexity:** O(1)

**Why this works:**
- We start from the largest possible width (√area) and work downward
- The first divisor we find will give us the rectangle closest to a square
- Since we ensure width ≤ √area, we automatically satisfy L ≥ W

### Example Walkthrough:
For area = 122122:
- √122122 ≈ 349.46, so we start with width = 349
- Check if 122122 % 349 == 0 → No
- Check if 122122 % 348 == 0 → No
- Continue until width = 286
- 122122 % 286 == 0 → Yes!
- Length = 122122 / 286 = 427
- Return [427, 286]

# Tags

- Math
- Number Theory
- Optimization
- Divisors/Factors

