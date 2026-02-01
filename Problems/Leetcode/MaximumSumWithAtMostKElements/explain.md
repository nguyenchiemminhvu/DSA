## Problem

https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/description/

```
You are given a 2D integer matrix grid of size n x m, an integer array limits of length n, 
and an integer k. The task is to find the maximum sum of at most k elements from the matrix 
grid such that:

The number of elements taken from the ith row of grid does not exceed limits[i].

Return the maximum sum.

Example 1:
Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
Output: 7
Explanation: From the second row, we can take at most 2 elements (4 and 3).
The maximum possible sum is 4 + 3 = 7.

Example 2:
Input: grid = [[5,3,7],[8,2,6]], limits = [2,2], k = 3
Output: 21
Explanation: From the first row, take at most 2 elements: 7 (could also take 5).
From the second row, take at most 2 elements: 8 and 6.
Maximum sum = 7 + 8 + 6 = 21.

Constraints:
- n == grid.length == limits.length
- m == grid[i].length
- 1 <= n, m <= 500
- 0 <= grid[i][j] <= 10^5
- 0 <= limits[i] <= m
- 0 <= k <= min(n * m, sum(limits))
```

## Observations

1. **Goal**: Select at most k elements from the grid to maximize the sum
2. **Row constraint**: From row i, we can select at most `limits[i]` elements
3. **Greedy approach**: To maximize sum, we should select the largest elements possible
4. **Two-level selection**:
   - First, for each row, select the largest `limits[i]` elements
   - Then, from all selected elements across all rows, pick the k largest

5. **Heap strategy**: 
   - Use a min-heap to efficiently filter out smaller elements
   - By popping from a min-heap, we keep the largest elements

## Solution

### Approach: Min-Heap to Keep Largest Elements

**Algorithm**:
1. **Row-level filtering**: For each row, keep only the `limits[i]` largest elements
   - Convert row to min-heap
   - Pop smallest elements until only `limits[i]` elements remain
   - These are the maximum `limits[i]` elements from this row

2. **Global filtering**: Collect all remaining elements and keep only k largest
   - Add all row-filtered elements to a global min-heap
   - Pop smallest elements until only k elements remain
   - These are the k largest elements respecting all constraints

3. **Calculate sum**: Return sum of remaining k elements

**Time Complexity**: O(n * m * log m)
- For each row: O(m log m) for heapify + O((m - limits[i]) * log m) for pops
- Global heap: O(total_elements * log total_elements)
- Where total_elements ≤ sum(limits) ≤ n * m

**Space Complexity**: O(n * m)
- Modified row arrays + global priority queue

**Code**:
```python
import heapq

class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        pq = []
        
        # For each row, keep only the largest limits[i] elements
        for i, row in enumerate(grid):
            heapq.heapify(row)  # Convert to min-heap
            
            # Remove smallest elements until we have limits[i] elements
            while len(row) > limits[i]:
                heapq.heappop(row)  # Remove minimum element
            
            # Add remaining (largest) elements from this row to global pool
            pq.extend(row)
        
        # From all collected elements, keep only the k largest
        heapq.heapify(pq)  # Convert to min-heap
        while len(pq) > k:
            heapq.heappop(pq)  # Remove minimum element
        
        return sum(pq)
```

**Example Trace** (Example 1):
- grid = [[1,2],[3,4]], limits = [1,2], k = 2
- Row 0: [1,2] → heapify → [1,2] → pop 1 (len > limits[0]=1) → [2]
- Row 1: [3,4] → heapify → [3,4] → no pops (len = limits[1]=2) → [3,4]
- Global pq: [2,3,4] → heapify → [2,3,4] → pop 2 (len > k=2) → [3,4]
- Sum = 3 + 4 = 7 ✓

**Alternative Approach**: 
Instead of modifying arrays, we could:
1. Sort each row in descending order, take first `limits[i]` elements
2. Merge all selected elements, sort descending, take first k elements
3. Return sum

This would be cleaner but potentially slower: O(n * m * log m) for sorting.

# Tags

`Greedy` `Heap (Priority Queue)` `Array` `Sorting`

