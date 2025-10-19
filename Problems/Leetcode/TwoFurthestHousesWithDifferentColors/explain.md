## Problem

https://leetcode.com/problems/two-furthest-houses-with-different-colors/

```
There are n houses evenly lined up on the street, and each house is beautifully painted. You are given a 0-indexed integer array colors of length n, where colors[i] represents the color of the ith house.

Return the maximum distance between two houses with different colors.

The distance between the ith and jth houses is abs(i - j), where abs(x) is the absolute value of x.

Example 1:

Input: colors = [1,1,1,6,1,1,1]
Output: 3
Explanation: In the above image, color 1 is blue, and color 6 is red.
The furthest two houses with different colors are house 0 and house 3.
House 0 has color 1, and house 3 has color 6. The distance between them is abs(0 - 3) = 3.
Note that houses 3 and 6 can also produce the optimal answer.

Example 2:

Input: colors = [1,8,3,8,3]
Output: 4
Explanation: In the above image, color 1 is blue, color 8 is yellow, and color 3 is green.
The furthest two houses with different colors are house 0 and house 4.
House 0 has color 1, and house 4 has color 3. The distance between them is abs(0 - 4) = 4.

Example 3:

Input: colors = [0,1]
Output: 1
Explanation: The furthest two houses with different colors are house 0 and house 1.
House 0 has color 0, and house 1 has color 1. The distance between them is abs(0 - 1) = 1.

Constraints:

n == colors.length
2 <= n <= 100
0 <= colors[i] <= 100
Test data are generated such that at least two houses have different colors.
```

## Observations

1. **Goal**: Find the maximum distance between two houses with different colors
2. **Distance formula**: `abs(i - j)` where i and j are indices of houses
3. **Key insight**: To maximize distance, we want to consider the extreme positions (first and last occurrence) of each color
4. **Constraint guarantee**: At least two houses have different colors, so a solution always exists
5. **Brute force approach**: Compare every pair of houses - O(n²) time
6. **Optimized approach**: Group houses by color and only compare extreme positions of different colors

## Solution

The provided solution uses a **grouping and extremes comparison** approach:

### Algorithm Steps:
1. **Group by color**: Create a dictionary where each color maps to a list of all its positions
2. **Extract position lists**: Convert the dictionary values to a list of position arrays
3. **Compare extremes**: For each pair of different colors, check all combinations of their extreme positions (first and last occurrence)

### Time Complexity: 
- **Grouping phase**: O(n) to iterate through all houses
- **Comparison phase**: O(c²) where c is the number of distinct colors
- **Overall**: O(n + c²), which is O(n) in practice since c ≤ n and typically c << n

### Space Complexity: O(n) for storing the color-to-positions mapping

### Why This Works:
- For any two different colors, the maximum distance will always be achieved by comparing their extreme positions
- We don't need to check all intermediate positions since they can't produce a larger distance than the extremes
- The four comparisons ensure we find the maximum among all possible extreme combinations

### Example Walkthrough:
For `colors = [1,1,1,6,1,1,1]`:
- Color 1 positions: [0,1,2,4,5,6] → extremes: 0 and 6
- Color 6 positions: [3] → extremes: 3 and 3
- Distances: |0-3|=3, |6-3|=3
- Maximum: 3

## Tags

array, greedy