## Problem

https://leetcode.com/problems/paint-house-iv/

You are given an even integer `n` representing the number of houses arranged in a straight line, and a 2D array `cost` of size `n x 3`, where `cost[i][j]` represents the cost of painting house `i` with color `j + 1` (colors are 1, 2, 3).

The houses look beautiful if they satisfy:
1. **No adjacent constraint**: No two adjacent houses are painted the same color.
2. **Equidistant constraint**: Houses equidistant from the ends are not painted the same color.
   - For n = 6: (0,5), (1,4), (2,3) are equidistant pairs.

**Return** the minimum cost to paint all houses satisfying both constraints.

### Constraints
- 2 ≤ n ≤ 10⁵
- n is even
- cost.length == n
- cost[i].length == 3
- 0 ≤ cost[i][j] ≤ 10⁵

## Observations

1. **Pairing Structure**: Since houses equidistant from ends cannot have the same color, we can view the problem as painting `n/2` pairs of houses simultaneously:
   - Pair 0: houses (0, n-1)
   - Pair 1: houses (1, n-2)
   - Pair i: houses (i, n-1-i)

2. **DP State Design**: At each pair, we need to track:
   - The current pair index `i`
   - The color of the previous left house (to enforce no-adjacent constraint)
   - The color of the previous right house (to enforce no-adjacent constraint)

3. **Color Validation Rules** for pair i with colors (c1, c2):
   - c1 ≠ left_color (no adjacent constraint on left side)
   - c2 ≠ c1 (adjacent constraint within the pair)
   - c2 ≠ right_color (no adjacent constraint on right side)
   - c1 ≠ c2 (implicit from the pair constraint)

4. **Meet-in-the-Middle**: By processing both ends simultaneously, we reduce the state space from trying all sequences to meeting in the middle.

## Solution

### Approach: Dynamic Programming with Memoization

The key insight is to process pairs of equidistant houses together and track the colors chosen for each pair's adjacent neighbors.

```python
def minCost(self, n: int, cost: List[List[int]]) -> int:
    from functools import lru_cache
    
    @lru_cache(None)
    def F(i: int, left_color: int, right_color: int) -> int:
        # i: current pair index (0 to n//2 - 1)
        # left_color: color of the left house in pair i-1 (or -1 if i == 0)
        # right_color: color of the right house in pair i-1 (or -1 if i == 0)
        
        # Base case: processed all n//2 pairs
        if i >= n // 2:
            return 0
        
        res = float('inf')
        
        # Try all color combinations for the left house at position i
        for c1 in range(3):
            if c1 == left_color:  # Violates no-adjacent constraint
                continue
            
            # Try all color combinations for the right house at position n-i-1
            for c2 in range(3):
                if c2 == c1 or c2 == right_color:  # Violates constraints
                    continue
                
                # Paint left house with c1, right house with c2
                # Recursively solve for the next pair
                res = min(
                    res,
                    cost[i][c1] + cost[n - i - 1][c2] + F(i + 1, c1, c2)
                )
        
        return res
    
    # Start with no previous colors (-1 indicates no constraint)
    return F(0, -1, -1)
```

### Detailed Walkthrough

**Example 1**: n = 4, cost = [[3,5,7],[6,2,9],[4,8,1],[7,3,5]]

The pairs are: (0, 3) and (1, 2)

```
F(0, -1, -1):  # Paint houses 0 and 3
  Try c1 = 0 (color 1, cost = 3):
    Try c2 = 1 (color 2, cost = 3):
      Cost so far: 3 + 3 = 6
      F(1, 0, 1):  # Paint houses 1 and 2 with constraints
        Try c1 = 1 (color 2, cost = 2):
          Try c2 = 0 (color 1, cost = 4):
            But c2 == 0 which equals left_color, skip
          Try c2 = 2 (color 3, cost = 1):
            Cost: 6 + 2 + 1 = 9
            F(2, 1, 2): returns 0 (base case)
            Total: 9 ✓
        Try c1 = 2 (color 3, cost = 9):
          ...
```

### Complexity Analysis

- **Time Complexity**: O(n/2 × 3 × 3) = O(n)
  - n/2 pairs to process
  - 3 colors for left house
  - 3 colors for right house
  - Memoization caches 3^3 = 27 possible states at each position

- **Space Complexity**: O(n)
  - Recursion depth: O(n)
  - Memoization cache: O(n) states

# Tags

#DP #Memoization #MeetInTheMiddle #Constraint-Satisfaction

