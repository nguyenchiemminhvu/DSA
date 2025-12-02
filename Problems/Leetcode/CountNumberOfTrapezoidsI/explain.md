## Problem

https://leetcode.com/problems/count-number-of-trapezoids-i/

You are given a 2D integer array `points`, where `points[i] = [xi, yi]` represents the coordinates of the ith point on the Cartesian plane.

A horizontal trapezoid is a convex quadrilateral with at least one pair of horizontal sides (i.e. parallel to the x-axis). Two lines are parallel if and only if they have the same slope.

Return the number of unique horizontal trapezoids that can be formed by choosing any four distinct points from `points`.

Since the answer may be very large, return it modulo 10^9 + 7.

**Example 1:**
- Input: `points = [[1,0],[2,0],[3,0],[2,2],[3,2]]`
- Output: `3`
- Explanation: Three distinct trapezoids can be formed:
  - Using points [1,0], [2,0], [3,2], and [2,2]
  - Using points [2,0], [3,0], [3,2], and [2,2]
  - Using points [1,0], [3,0], [3,2], and [2,2]

**Example 2:**
- Input: `points = [[0,0],[1,0],[0,1],[2,1]]`
- Output: `1`

**Constraints:**
- 4 <= points.length <= 10^5
- -10^8 <= xi, yi <= 10^8
- All points are pairwise distinct

## Observations

1. **Horizontal Trapezoid Definition**: A trapezoid with at least one pair of horizontal parallel sides means we need two horizontal lines (points with the same y-coordinate).

2. **Structure**: To form a horizontal trapezoid, we need:
   - 2 points on one horizontal line (same y-coordinate)
   - 2 points on another horizontal line (different y-coordinate)
   - Total: 4 distinct points

3. **Counting Strategy**: 
   - Group points by their y-coordinates
   - For each pair of horizontal lines (y1 and y2), count combinations
   - If line y1 has `n1` points and line y2 has `n2` points:
     - Ways to choose 2 points from y1: C(n1, 2) = n1 * (n1 - 1) / 2
     - Ways to choose 2 points from y2: C(n2, 2) = n2 * (n2 - 1) / 2
     - Total combinations: C(n1, 2) × C(n2, 2)

4. **Optimization**: Process y-coordinates in sorted order to avoid counting duplicates and efficiently accumulate results.

## Solution

1. **Group by Y-coordinate** (Lines 3-7):
   - Create a dictionary `map_y` where key = y-coordinate, value = list of x-coordinates
   - This groups all points that lie on the same horizontal line

2. **Filter Valid Lines** (Line 9):
   - Only consider y-coordinates with at least 2 points (needed to form a horizontal side)
   - Sort these y-coordinates for systematic processing

3. **Count Trapezoids** (Lines 11-16):
   - `count_pairs`: Accumulates the total number of point pairs from all previously processed horizontal lines
   - For each horizontal line at height `y`:
     - Calculate pairs that can be formed: `pair = n * (n - 1) // 2`
     - Multiply by `count_pairs` to get trapezoids formed with this line and all previous lines
     - Add `pair` to `count_pairs` for future iterations
   
4. **Example Walkthrough** (Example 1):
   - Points: [[1,0],[2,0],[3,0],[2,2],[3,2]]
   - map_y: {0: [1,2,3], 2: [2,3]}
   - arr_y: [0, 2]
   - Iteration 1 (y=0): n=3, pair=3, res=0+(3*0)=0, count_pairs=3
   - Iteration 2 (y=2): n=2, pair=1, res=0+(1*3)=3, count_pairs=4
   - Result: 3

**Time Complexity**: O(n log n) - dominated by sorting y-coordinates
**Space Complexity**: O(n) - for the hashmap storing points

# Tags
#geometry #combinatorics #hashmap #math

