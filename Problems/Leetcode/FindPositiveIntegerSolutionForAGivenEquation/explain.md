## Problem

https://leetcode.com/problems/find-positive-integer-solution-for-a-given-equation/description/

```
Given a callable function f(x, y) with a hidden formula and a value z, return all positive 
integer pairs x and y where f(x,y) == z. You may return the pairs in any order.

The function is monotonically increasing:
- f(x, y) < f(x + 1, y)
- f(x, y) < f(x, y + 1)

Constraints:
- 1 <= function_id <= 9
- 1 <= z <= 100
- Solutions will be in range 1 <= x, y <= 1000
- f(x, y) fits in 32-bit signed integer for 1 <= x, y <= 1000

Examples:
- function_id = 1 (f(x,y) = x + y), z = 5 → [[1,4],[2,3],[3,2],[4,1]]
- function_id = 2 (f(x,y) = x * y), z = 5 → [[1,5],[5,1]]
```

## Observations

1. **Monotonic Property**: Since f(x, y) is strictly increasing in both x and y:
   - Increasing x makes f(x, y) larger
   - Increasing y makes f(x, y) larger
   - Decreasing x makes f(x, y) smaller
   - Decreasing y makes f(x, y) smaller

2. **Two-Pointer Feasibility**: The monotonic property allows us to use a two-pointer approach similar 
   to searching in a sorted 2D matrix where rows and columns are sorted.

3. **Search Space**: We start from opposite corners:
   - x = 1 (minimum possible value)
   - y = 1000 (maximum possible value)
   
4. **Movement Strategy**:
   - If f(x, y) == z: Found a solution, record it
   - If f(x, y) < z: Need larger value → increase x
   - If f(x, y) > z: Need smaller value → decrease y

5. **Why This Works**: 
   - When f(x, y) < z, increasing y would make it even larger, but we're already at max useful y
   - When f(x, y) > z, decreasing x would make it smaller, but we need to try smaller y first
   - This ensures we explore all valid pairs without missing any

## Solution

**Approach: Two-Pointer Technique**

The solution uses a two-pointer approach starting from opposite corners of the search space:

```python
class Solution:
    def findSolution(self, custom: 'CustomFunction', z: int) -> List[List[int]]:
        res = []
        x = 1      # Start at minimum x
        y = 1000   # Start at maximum y
        
        while x <= 1000 and y >= 1:
            value = custom.f(x, y)
            
            if value == z:
                res.append([x, y])
                x += 1  # Move to next potential pair
                y -= 1  # Both pointers move inward
            elif value < z:
                x += 1  # Need larger value, increase x
            else:  # value > z
                y -= 1  # Need smaller value, decrease y
        
        return res
```

**Algorithm Steps**:

1. Initialize two pointers: x = 1 (min), y = 1000 (max)
2. While both pointers are within valid range [1, 1000]:
   - Evaluate f(x, y)
   - If equals z: add pair [x, y] to results, move both pointers inward
   - If less than z: increase x (need larger value)
   - If greater than z: decrease y (need smaller value)
3. Return all found pairs

**Time Complexity**: O(x + y) = O(1000 + 1000) = O(1) or O(√z) to O(z) depending on the formula
- In worst case, we traverse at most 2000 steps (from x=1 to x=1000 or y=1000 to y=1)
- Each function call is O(1)

**Space Complexity**: O(1) excluding the output array
- Only uses constant extra space for x, y, and value variables

**Why It's Optimal**:
- Avoids brute force O(n²) approach of checking all 1000 × 1000 pairs
- Intelligently prunes the search space using the monotonic property
- Each step eliminates either an entire row or column from consideration

# Tags

