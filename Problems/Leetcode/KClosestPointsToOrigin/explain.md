## Problem

https://leetcode.com/problems/k-closest-points-to-origin/description/

```
Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane 
and an integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance 
(i.e., √(x1 - x2)² + (y1 - y2)²).

You may return the answer in any order. The answer is guaranteed to be unique 
(except for the order that it is in).

Example 1:
Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.

Example 2:
Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]

Constraints:
- 1 <= k <= points.length <= 10^4
- -10^4 <= xi, yi <= 10^4
```

## Observations

1. **Distance Calculation Optimization**: We don't need to calculate the actual Euclidean distance using `sqrt()`. Since we're only comparing distances, we can use the squared distance `x² + y²`. This avoids expensive square root operations and maintains the same ordering.

2. **We need K smallest elements**: This is a classic "top K" problem where we need to find the K elements with the smallest values (distances).

3. **Heap-based approach**: Using a max heap of size k is efficient:
   - We maintain only k elements in memory at any time
   - The largest element (farthest point) is always at the top
   - When we find a closer point, we can remove the farthest one

4. **Time Complexity Trade-offs**:
   - **Max Heap approach**: O(n log k) - iterate through all points, each heap operation is O(log k)
   - **Min Heap approach**: O(n log n) - heapify all points then extract k elements
   - **Quick Select**: O(n) average case, O(n²) worst case
   - **Sorting**: O(n log n) - sort all points by distance

5. **Why Max Heap with size K?**
   - We keep the k closest points seen so far
   - The root of the max heap is the farthest of these k points
   - When we encounter a new point closer than the root, we pop the root and push the new point
   - This ensures we always maintain the k closest points

## Solution

### Approach: Max Heap of Size K

```python
import heapq

class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        pq = []
        for x, y in points:
            # Use negative distance for max heap (Python heapq is min heap by default)
            heapq.heappush(pq, (-(x**2 + y**2), (x, y)))
            if len(pq) > k:
                heapq.heappop(pq)
        
        return [item[1] for item in pq]
```

### How it Works:

1. **Initialize empty heap**: `pq = []`

2. **Process each point**:
   - Calculate squared distance: `x² + y²`
   - Use negative distance: `-(x² + y²)` to simulate max heap (Python's heapq is min heap)
   - Push tuple: `(negative_distance, (x, y))`
   
3. **Maintain heap size**:
   - If heap size exceeds k, pop the element with the largest distance (root)
   - This ensures we keep only the k closest points

4. **Extract result**:
   - After processing all points, heap contains exactly k closest points
   - Extract the coordinates: `[item[1] for item in pq]`

### Example Walkthrough:

**Input**: `points = [[3,3],[5,-1],[-2,4]], k = 2`

| Step | Point | Distance² | Heap (negative distances) | Action |
|------|-------|-----------|---------------------------|--------|
| 1 | [3,3] | 18 | [(-18, (3,3))] | Push |
| 2 | [5,-1] | 26 | [(-26, (5,-1)), (-18, (3,3))] | Push |
| 3 | [-2,4] | 20 | [(-26, (5,-1)), (-18, (3,3)), (-20, (-2,4))] | Push |
| 4 | - | - | [(-20, (-2,4)), (-18, (3,3))] | Pop (5,-1) since len > k |

**Output**: `[[3,3], [-2,4]]` (order may vary)

### Complexity Analysis:

- **Time Complexity**: O(n log k)
  - Iterate through n points: O(n)
  - Each heap push: O(log k)
  - Each heap pop (at most n times): O(log k)
  - Total: O(n log k)

- **Space Complexity**: O(k)
  - Heap stores at most k elements
  - Result array stores k elements

### Alternative Approaches:

1. **Min Heap (all points)**:
```python
def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
    heap = [(x**2 + y**2, [x, y]) for x, y in points]
    heapq.heapify(heap)  # O(n)
    return [heapq.heappop(heap)[1] for _ in range(k)]  # O(k log n)
```
Time: O(n + k log n), Space: O(n)

2. **Sorting**:
```python
def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
    points.sort(key=lambda p: p[0]**2 + p[1]**2)
    return points[:k]
```
Time: O(n log n), Space: O(1) or O(n) depending on sort implementation

### Why the Max Heap Approach is Better:

- **Memory Efficient**: Only stores k elements instead of n
- **Better for streaming data**: Can process points one at a time
- **Optimal for k << n**: When k is much smaller than n, O(n log k) is significantly better than O(n log n)

# Tags

`Heap` `Priority Queue` `Array` `Sorting` `Divide and Conquer` `Quickselect` `Math` `Geometry`

