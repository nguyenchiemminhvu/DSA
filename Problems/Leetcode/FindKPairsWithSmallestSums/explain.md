## Problem

https://leetcode.com/problems/find-k-pairs-with-smallest-sums/

```
You are given two integer arrays nums1 and nums2 sorted in non-decreasing order and an integer k.

Define a pair (u, v) which consists of one element from the first array and one element from the second array.

Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.

Example 1:
Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

Example 2:
Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Explanation: The first 2 pairs are returned from the sequence: [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

Constraints:
- 1 <= nums1.length, nums2.length <= 10^5
- -10^9 <= nums1[i], nums2[i] <= 10^9
- nums1 and nums2 both are sorted in non-decreasing order.
- 1 <= k <= 10^4
- k <= nums1.length * nums2.length
```

## Observations

1. **Sorted Arrays**: Both input arrays are sorted in non-decreasing order, which means the smallest possible pair sum starts at `(nums1[0], nums2[0])`.

2. **Brute Force Approach**: A naive solution would generate all possible pairs `(nums1[i], nums2[j])` for all i and j, then sort by sum and take the first k pairs. However, this would be O(n1 * n2 * log(n1 * n2)), which is inefficient for large arrays.

3. **Optimization with Min-Heap**: Since arrays are sorted, we can use a min-heap to efficiently explore pairs in order of increasing sum:
   - Start with the smallest pair `(nums1[0], nums2[0])`
   - For each extracted pair at indices `(i, j)`, the next potentially smallest pairs are at `(i+1, j)` and `(i, j+1)`
   - This is similar to merging k sorted lists

4. **Avoid Duplicates**: We need to track visited pairs to avoid adding the same pair multiple times to the heap.

5. **Early Termination**: We only need k pairs, so we can stop once we've found k pairs.

## Solution

**Algorithm: Min-Heap with BFS-like Exploration**

The solution uses a min-heap (priority queue) to efficiently find the k smallest pair sums:

1. **Initialize**:
   - Create a min-heap with the first pair `(nums1[0], nums2[0])` and its sum
   - Use a visited set to track explored index pairs
   - Initialize result list for storing k smallest pairs

2. **Extract and Expand**:
   - Pop the pair with minimum sum from the heap
   - Add this pair to the result
   - Explore two potential next smallest pairs:
     - `(i+1, j)`: Move to next element in nums1
     - `(i, j+1)`: Move to next element in nums2
   - Add unvisited neighbors to the heap

3. **Repeat**: Continue until we have k pairs or heap is empty

4. **Return**: Convert index pairs to actual value pairs

**Time Complexity**: O(k * log(k))
- We extract k elements from the heap
- Each heap operation takes O(log(k)) time
- In worst case, heap size can grow to O(k)

**Space Complexity**: O(k)
- Heap stores at most O(k) elements
- Visited set stores at most O(k) pairs
- Result list stores k pairs

**Code**:
```python
import heapq

class Solution:
    def kSmallestPairs(self, nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:
        n1, n2 = len(nums1), len(nums2)
        i1 = i2 = 0
        smallest_pairs = []
        
        # Min-heap: stores (sum, (index1, index2))
        pq = [(nums1[i1] + nums2[i2], (i1, i2))]
        visited = set()
        visited.add((i1, i2))
        
        while pq and len(smallest_pairs) < k:
            sum_pair, (i1, i2) = heapq.heappop(pq)
            smallest_pairs.append([i1, i2])
            
            # Explore two directions: right in nums1, right in nums2
            for j1, j2 in [(i1 + 1, i2), (i1, i2 + 1)]:
                if j1 < n1 and j2 < n2 and (j1, j2) not in visited:
                    visited.add((j1, j2))
                    heapq.heappush(pq, (nums1[j1] + nums2[j2], (j1, j2)))
        
        # Convert indices to actual values
        return [[nums1[i], nums2[j]] for i, j in smallest_pairs[:k]]
```

**Key Points**:
- The heap always contains pairs in ascending order of their sums
- By exploring only `(i+1, j)` and `(i, j+1)`, we ensure we don't miss any smaller pairs
- The visited set prevents redundant exploration (e.g., `(i+1, j)` can be reached from both `(i, j)` and `(i+1, j-1)`)

# Tags
`heap`, `priority-queue`, `min-heap`, `two-pointers`, `sorted-arrays`, `greedy`, `bfs`

