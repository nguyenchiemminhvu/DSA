## Problem

https://leetcode.com/problems/maximum-height-of-a-triangle/description/

```
You are given two integers red and blue representing the count of red and blue colored balls. 
You have to arrange these balls to form a triangle such that the 1st row will have 1 ball, 
the 2nd row will have 2 balls, the 3rd row will have 3 balls, and so on.

All the balls in a particular row should be the same color, and adjacent rows should have different colors.

Return the maximum height of the triangle that can be achieved.

Example 1:
Input: red = 2, blue = 4
Output: 3
Explanation: Row 1: 1 blue, Row 2: 2 red, Row 3: 3 blue

Example 2:
Input: red = 2, blue = 1
Output: 2
Explanation: Row 1: 1 red, Row 2: 2 blue

Example 3:
Input: red = 1, blue = 1
Output: 1

Example 4:
Input: red = 10, blue = 1
Output: 2
Explanation: Row 1: 1 blue, Row 2: 2 red (not enough blue for row 3)

Constraints:
- 1 <= red, blue <= 100
```

## Observations

1. **Triangle Structure**: Each row $i$ requires exactly $i$ balls (row 1 needs 1, row 2 needs 2, etc.)

2. **Alternating Colors**: Adjacent rows must have different colors, creating an alternating pattern

3. **Two Possible Patterns**:
   - Pattern A: Start with red (Red → Blue → Red → Blue...)
   - Pattern B: Start with blue (Blue → Red → Blue → Red...)

4. **Greedy Approach**: We can greedily build the triangle row by row until we run out of balls

5. **Key Insight**: Since we don't know which color should start, we must try both patterns and take the maximum height

6. **Ball Distribution**:
   - Odd rows (1, 3, 5, ...) use one color
   - Even rows (2, 4, 6, ...) use the other color
   - Total balls for odd rows: $1 + 3 + 5 + ... = n^2$ (where $n$ is number of odd rows)
   - Total balls for even rows: $2 + 4 + 6 + ... = n(n+1)$ (where $n$ is number of even rows)

## Solution

### Approach: Simulation with Both Starting Colors

**Algorithm**:
1. Try both possible starting configurations:
   - Start with red in row 1
   - Start with blue in row 1
2. For each configuration, simulate building the triangle:
   - Use an index to alternate between the two colors
   - For each row, check if we have enough balls of the current color
   - If yes, use the required balls and move to the next row
   - If no, stop and return the current height
3. Return the maximum height achieved from both configurations

**Implementation Details**:
- Use a list `[color1, color2]` to represent ball counts
- Use index modulo 2 to alternate: `idx = (idx + 1) % 2`
- Track the required balls for each row: starts at 1, increments by 1 each time

### Complexity Analysis

**Time Complexity**: $O(\sqrt{n})$ where $n = red + blue$
- Each configuration simulates building the triangle
- Maximum possible height is roughly $\sqrt{2n}$ (sum of first $k$ numbers = $\frac{k(k+1)}{2} \approx n$)
- We run two simulations, but this is still $O(\sqrt{n})$

**Space Complexity**: $O(1)$
- Only uses a constant amount of extra space for variables
- The input arrays are small (just 2 elements each)

### Example Walkthrough

**Example 1**: `red = 2, blue = 4`

*Configuration 1: Start with red*
- Row 1: Need 1 red → Use 1 red (red=1, blue=4)
- Row 2: Need 2 blue → Use 2 blue (red=1, blue=2)
- Row 3: Need 3 red → Not enough (only 1 red available) → Height = 2

*Configuration 2: Start with blue*
- Row 1: Need 1 blue → Use 1 blue (red=2, blue=3)
- Row 2: Need 2 red → Use 2 red (red=0, blue=3)
- Row 3: Need 3 blue → Use 3 blue (red=0, blue=0)
- Row 4: Need 4 red → Not enough → Height = 3

**Maximum Height = 3**

# Tags
#greedy #simulation #math #easy

