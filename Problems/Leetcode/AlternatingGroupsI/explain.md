## Problem

https://leetcode.com/problems/alternating-groups-i/description/

```
There is a circle of red and blue tiles. You are given an array of integers colors. The color of tile i is represented by colors[i]:

colors[i] == 0 means that tile i is red.
colors[i] == 1 means that tile i is blue.
Every 3 contiguous tiles in the circle with alternating colors (the middle tile has a different color from its left and right tiles) is called an alternating group.

Return the number of alternating groups.

Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.

Example 1:

Input: colors = [1,1,1]

Output: 0

Explanation:

Example 2:

Input: colors = [0,1,0,0,1]

Output: 3

Explanation:

Alternating groups:

Constraints:

3 <= colors.length <= 100
0 <= colors[i] <= 1
```

## Observations

1. **Circular Array**: The tiles form a circle, meaning the first and last elements are adjacent.
2. **Alternating Group Definition**: A group of 3 contiguous tiles where the middle tile has a different color from its left and right neighbors.
3. **Pattern Recognition**: We need to find triplets `[a, b, c]` where `a != b` and `b != c` (which also means `a == c` since colors are only 0 or 1).
4. **Edge Cases**: 
   - Arrays with all same colors will have 0 alternating groups
   - Need to handle the circular nature by considering wraparound cases
5. **Key Insight**: Since it's circular, we need to check groups that wrap around the end (e.g., last element, first element, second element).

## Solution

1. **Handle Circularity**: Extend the original array by appending the first two elements `[colors[0], colors[1]]`. This clever trick allows us to handle the circular nature without complex modular arithmetic.

2. **Iterate Through Middle Elements**: Loop from index 1 to `len(colors) - 2` (which covers the original array length plus handles wraparound cases).

3. **Check Alternating Condition**: For each position `i`, check if `colors[i-1] != colors[i] != colors[i+1]`. This condition ensures:
   - Left neighbor is different from middle tile
   - Middle tile is different from right neighbor
   - Implicitly, left and right neighbors are the same color

4. **Count Valid Groups**: Increment counter for each valid alternating group found.

**Example Walkthrough:**
- Input: `[0,1,0,0,1]`
- After extension: `[0,1,0,0,1,0,1]`
- Check positions 1-5:
  - i=1: `0 != 1 != 0` ✓ (group: 0,1,0)
  - i=2: `1 != 0 != 0` ✗ 
  - i=3: `0 != 0 != 1` ✗
  - i=4: `0 != 1 != 0` ✓ (group: 0,1,0 - wraparound)
  - i=5: `1 != 0 != 1` ✓ (group: 1,0,1 - wraparound)
- Result: 3 alternating groups

**Time Complexity:** O(n) - single pass through the array
**Space Complexity:** O(1) - only extending the array by 2 elements, which is constant

# Tags
Array, Simulation, Circular Array

