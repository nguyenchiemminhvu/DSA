## Problem

https://leetcode.com/problems/trapping-rain-water/description/

Given `n` non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

### Example 1

**Input:** `height = [0,1,0,2,1,0,1,3,2,1,2,1]`

**Output:** `6`

**Explanation:** The elevation map (black section) is represented by array `[0,1,0,2,1,0,1,3,2,1,2,1]`. In this case, 6 units of rain water (blue section) are being trapped.

```
       ███
    ██ ███  █
    ██ █ █ ██ █
 █  ███ █ ██ ██
 █  █ █ █ █ █ █
[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
```

### Example 2

**Input:** `height = [4,2,0,3,2,5]`

**Output:** `9`

### Constraints

- `n == height.length`
- `1 <= n <= 2 * 10^4`
- `0 <= height[i] <= 10^5`

## Observations

### Key Insight: Water Trapped Between Boundaries

Water can be trapped at position `i` if:
1. There exists a higher bar to the **left** of position `i`
2. There exists a higher bar to the **right** of position `i`
3. The water level at position `i` = `min(left_boundary, right_boundary) - height[i]`

### Approach Analysis

The solution uses a **monotonic stack with preprocessing** strategy:

1. **Monotonic Stack Phase (O(n)):**
   - Find the nearest greater element to the right for each position
   - Maintain a stack of indices in decreasing order of heights
   - When we find a taller bar, pop elements and record their right boundary

2. **Left Boundary Processing (O(n)):**
   - For each position, determine which bar on the left can trap water
   - The left boundary should be a **valid boundary** (not just any left bar)
   - Convert first-left-greater indices to left-maximum indices for proper water calculation

3. **Right Boundary Processing (O(n)):**
   - Similar to left processing, but traverse from right to left
   - Ensure right boundaries are maximum values encountered so far

4. **Water Calculation (O(n)):**
   - For each position that has both left and right boundaries, calculate trapped water
   - Water trapped = `min(left_height, right_height) - current_height`

### Why This Works

- A bar can trap water only if it's **enclosed** between two higher bars
- The water level at any position is determined by the **minimum** of the left and right boundaries
- By preprocessing to find valid boundaries (actual maximum heights), we avoid counting water incorrectly

### Complexity Analysis

- **Time Complexity:** O(n) - Single pass with stack operations
- **Space Complexity:** O(n) - For left_greater, right_greater arrays and stack

## Solution

```python
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        
        # Step 1: Initialize boundary arrays
        # left_greater[i] = index of left boundary (initialized to -1, meaning no left boundary)
        # right_greater[i] = index of right boundary (initialized to n, meaning no right boundary)
        left_greater = [-1] * n
        right_greater = [n] * n
        
        # Step 2: Use monotonic stack to find nearest greater element to the right
        # Stack stores indices in decreasing order of their heights
        st = []
        for i in range(n):
            # While current bar is taller than stack top, 
            # we found the right boundary for stack top
            while st and height[st[-1]] < height[i]:
                right_greater[st[-1]] = i
                st.pop()
            
            # The first element greater than current (if exists) is on the left
            if st:
                left_greater[i] = st[-1]
            
            st.append(i)
        
        # Step 3: Refine left boundaries - ensure they represent actual maximum heights
        # Traverse left to right and replace with actual left maximum indices
        left_max_idx = 0
        for i in range(1, n):
            # If there's a left boundary, but left max is greater than left boundary,
            # use left max as the boundary
            if left_greater[i] != -1 and height[left_max_idx] > height[left_greater[i]]:
                left_greater[i] = left_max_idx
            
            # Update left max if current is taller
            if height[left_max_idx] < height[i]:
                left_max_idx = i
        
        # Step 4: Refine right boundaries - ensure they represent actual maximum heights
        # Traverse right to left and replace with actual right maximum indices
        right_max_idx = n - 1
        for i in range(n - 2, -1, -1):
            # If there's a right boundary, but right max is greater than right boundary,
            # use right max as the boundary
            if right_greater[i] != n and height[right_max_idx] > height[right_greater[i]]:
                right_greater[i] = right_max_idx
            
            # Update right max if current is taller
            if height[right_max_idx] < height[i]:
                right_max_idx = i
        
        # Step 5: Calculate trapped water
        res = 0
        for i in range(n):
            left = left_greater[i]
            right = right_greater[i]
            
            # Only count water if position is enclosed by both boundaries
            if left != -1 and right != n:
                water_level = min(height[left], height[right])
                trapped_water = water_level - height[i]
                res += trapped_water
        
        return res
```

### Step-by-Step Example Walkthrough

**Input:** `[0,1,0,2,1,0,1,3,2,1,2,1]`

**Step 1-2: Monotonic Stack Phase**
```
Index:  0 1 2 3 4 5 6 7 8 9 10 11
Height: 0 1 0 2 1 0 1 3 2 1 2  1

left_greater:  [-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
right_greater: [1, 3, 3, 7, 7, 6, 7, 12, 12, 10, 12, 12]
```

**Step 3-4: Boundary Refinement**
```
After left refinement:  [-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
After right refinement: [1, 3, 3, 7, 7, 6, 7, 12, 12, 10, 12, 12]
```

**Step 5: Water Calculation**
```
Position 2: left=1(h=1), right=3(h=2) → min(1,2) - 0 = 1
Position 4: left=3(h=2), right=7(h=3) → min(2,3) - 1 = 1
Position 5: left=6(h=1), right=7(h=3) → min(1,3) - 0 = 1
...total = 6
```

# Tags

- Array
- Stack
- Monotonic Stack
- Two Pointers
- Dynamic Programming
- O(n) Time Complexity
- LeetCode Hard

