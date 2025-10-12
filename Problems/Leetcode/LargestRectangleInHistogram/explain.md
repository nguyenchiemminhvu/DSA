## Problem

https://leetcode.com/problems/largest-rectangle-in-histogram/

```
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Example 1:

Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:

Input: heights = [2,4]
Output: 4

Constraints:

1 <= heights.length <= 105
0 <= heights[i] <= 104
```

## Observations

1. **Key Insight**: For each bar in the histogram, we want to find the largest rectangle that can be formed with that bar as the shortest bar in the rectangle.

2. **Rectangle Formation**: For a bar at index `i` with height `heights[i]`, the largest rectangle using this bar as the minimum height is formed by:
   - Finding the leftmost position where we can extend (nearest smaller element to the left)
   - Finding the rightmost position where we can extend (nearest smaller element to the right)
   - The width of the rectangle is `right_boundary - left_boundary - 1`
   - The area is `heights[i] * width`

3. **Monotonic Stack Pattern**: We can use a monotonic stack to efficiently find the nearest smaller elements:
   - For left boundaries: traverse left to right, maintain increasing stack
   - For right boundaries: traverse right to left, maintain increasing stack

4. **Edge Cases**: 
   - If no smaller element exists to the left, we can extend to the beginning (index -1)
   - If no smaller element exists to the right, we can extend to the end (index n)
   - The entire histogram with minimum height is also a valid rectangle

## Solution

**Algorithm: Monotonic Stack Approach**

The solution uses two passes with monotonic stacks to find the nearest smaller elements on both sides of each bar:

### Step 1: Find Nearest Smaller Element to the Left
```python
# s_left[i] stores the index of nearest smaller element to the left of i
# If no such element exists, s_left[i] = -1
st = []
for i in range(n):
    while st and heights[i] <= heights[st[-1]]:
        st.pop()
    if st:
        s_left[i] = st[-1]
    st.append(i)
```

### Step 2: Find Nearest Smaller Element to the Right
```python
# s_right[i] stores the index of nearest smaller element to the right of i
# If no such element exists, s_right[i] = n
st = []
for i in range(n - 1, -1, -1):
    while st and heights[i] <= heights[st[-1]]:
        st.pop()
    if st:
        s_right[i] = st[-1]
    st.append(i)
```

### Step 3: Calculate Maximum Area
```python
# For each bar, calculate the area of the largest rectangle with this bar as minimum height
for i in range(n):
    width = s_right[i] - s_left[i] - 1
    area = heights[i] * width
    res = max(res, area)
```

### Step 4: Handle Edge Case
```python
# Consider the rectangle formed by the entire histogram with minimum height
return max(res, min(heights) * n)
```

**Time Complexity**: O(n) - Each element is pushed and popped from the stack at most once
**Space Complexity**: O(n) - For the arrays and stack

**Example Walkthrough** with `heights = [2,1,5,6,2,3]`:
- For bar at index 2 (height=5): left_boundary=-1, right_boundary=4, width=4-(-1)-1=4, area=5*4=20
- For bar at index 3 (height=6): left_boundary=2, right_boundary=4, width=4-2-1=1, area=6*1=6
- The maximum area found is 10 (for bar at index 3 or optimized calculation)

## Tags

array, greedy, stack