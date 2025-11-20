## Problem

https://leetcode.com/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/description/

```
You are given two integers, x and y, which represent your current location on a Cartesian grid: (x, y). You are also given an array points where each points[i] = [ai, bi] represents that a point exists at (ai, bi). A point is valid if it shares the same x-coordinate or the same y-coordinate as your location.

Return the index (0-indexed) of the valid point with the smallest Manhattan distance from your current location. If there are multiple, return the valid point with the smallest index. If there are no valid points, return -1.

The Manhattan distance between two points (x1, y1) and (x2, y2) is abs(x1 - x2) + abs(y1 - y2).

Example 1:

Input: x = 3, y = 4, points = [[1,2],[3,1],[2,4],[2,3],[4,4]]
Output: 2
Explanation: Of all the points, only [3,1], [2,4] and [4,4] are valid. Of the valid points, [2,4] and [4,4] have the smallest Manhattan distance from your current location, with a distance of 1. [2,4] has the smallest index, so return 2.

Example 2:

Input: x = 3, y = 4, points = [[3,4]]
Output: 0
Explanation: The answer is allowed to be on the same location as your current location.

Example 3:

Input: x = 3, y = 4, points = [[2,3]]
Output: -1
Explanation: There are no valid points.

Constraints:

1 <= points.length <= 104
points[i].length == 2
1 <= x, y, ai, bi <= 104
```

## Observations

1. **Valid Points**: A point is valid if it shares either the same x-coordinate OR the same y-coordinate as our current location (x, y).

2. **Distance Metric**: We need to find the point with the smallest Manhattan distance, which is `abs(x1 - x2) + abs(y1 - y2)`.

3. **Tie Breaking**: If multiple points have the same smallest distance, we should return the one with the smallest index in the original array.

4. **Edge Cases**: 
   - No valid points exist → return -1
   - Point at the same location as current position is valid with distance 0

5. **Key Insight**: Since we only consider points that share x OR y coordinate:
   - If point shares x-coordinate: distance = `abs(y1 - y2)` 
   - If point shares y-coordinate: distance = `abs(x1 - x2)`

## Solution

The provided solution has a **critical bug** in the distance function. Let me explain:

### Issue with Current Implementation
```python
def dist(xx: int, yy: int) -> int:
    return max(abs(xx - x), abs(yy - y))  # This calculates Chebyshev distance, not Manhattan!
```

This calculates the **Chebyshev distance** (max of coordinate differences), but the problem asks for **Manhattan distance** (sum of coordinate differences).

### Correct Approach

```python
class Solution:
    def nearestValidPoint(self, x: int, y: int, points: List[List[int]]) -> int:
        min_distance = float('inf')
        result_index = -1
        
        for i, (px, py) in enumerate(points):
            # Check if point is valid (shares x or y coordinate)
            if px == x or py == y:
                # Calculate Manhattan distance
                manhattan_dist = abs(px - x) + abs(py - y)
                
                # Update result if this distance is smaller
                if manhattan_dist < min_distance:
                    min_distance = manhattan_dist
                    result_index = i
        
        return result_index
```

### Algorithm Steps:
1. **Initialize**: Set minimum distance to infinity and result index to -1
2. **Iterate**: Through all points with their indices
3. **Filter**: Only consider valid points (same x OR same y coordinate)
4. **Calculate**: Manhattan distance for each valid point
5. **Update**: Keep track of the point with minimum distance and smallest index
6. **Return**: The index of the closest valid point, or -1 if none found

### Time Complexity: O(n) - single pass through all points
### Space Complexity: O(1) - only using constant extra space

### Example Walkthrough:
- Input: x=3, y=4, points=[[1,2],[3,1],[2,4],[2,3],[4,4]]
- Valid points: [3,1] (same x), [2,4] (same y), [4,4] (same y)
- Distances: [3,1]→3, [2,4]→1, [4,4]→1  
- Both [2,4] and [4,4] have distance 1, but [2,4] has smaller index (2 vs 4)
- Return: 2

# Tags

Array, Math, Manhattan Distance, Linear Search

