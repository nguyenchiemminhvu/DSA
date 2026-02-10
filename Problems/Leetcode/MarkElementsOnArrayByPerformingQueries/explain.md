## Problem

https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/description/

```
You are given a 0-indexed array nums of size n consisting of positive integers.

You are also given a 2D array queries of size m where queries[i] = [indexi, ki].

Initially all elements of the array are unmarked.

You need to apply m queries on the array in order, where on the ith query you do the following:

1. Mark the element at index indexi if it is not already marked.
2. Then mark ki unmarked elements in the array with the smallest values. If multiple such elements exist, 
   mark the ones with the smallest indices. And if less than ki unmarked elements exist, then mark all of them.

Return an array answer of size m where answer[i] is the sum of unmarked elements in the array after the ith query.

Example 1:
Input: nums = [1,2,2,1,2,3,1], queries = [[1,2],[3,3],[4,2]]
Output: [8,3,0]

Example 2:
Input: nums = [1,4,2,3], queries = [[0,1]]
Output: [7]

Constraints:
- n == nums.length
- m == queries.length
- 1 <= m <= n <= 10^5
- 1 <= nums[i] <= 10^5
- queries[i].length == 2
- 0 <= indexi, ki <= n - 1
```

## Observations

1. **Two-step marking process**: Each query has two parts:
   - Mark element at specific index
   - Mark k smallest unmarked elements (with tie-breaking by smallest index)

2. **Priority-based selection**: We need to efficiently find the k smallest unmarked elements, which suggests using a min-heap (priority queue).

3. **Order matters**: The natural ordering should be by value first, then by index for tie-breaking: `(value, index)`.

4. **Tracking marked elements**: We need a way to quickly check if an element is already marked (set).

5. **Running sum**: Instead of recalculating the sum after each query, we can maintain a running sum and subtract marked elements.

6. **Lazy deletion**: When popping from heap, we may encounter already-marked elements. We skip them until we find an unmarked one.

## Solution

### Approach: Min-Heap + Set

**Key Idea**: Use a min-heap to maintain elements sorted by (value, index) and a set to track marked indices.

**Algorithm**:

1. **Initialize**:
   - Create a min-heap with all elements as `(value, index)` tuples
   - Initialize a set to track marked indices
   - Calculate the initial sum of all elements
   - Prepare result array

2. **Process each query** `[idx, k]`:
   - **Step 1**: Mark element at index `idx` if not already marked
     - Add to marked set
     - Subtract from running sum
   
   - **Step 2**: Mark k smallest unmarked elements
     - Pop from heap until we find an unmarked element (lazy deletion)
     - Mark it and subtract from sum
     - Repeat k times (or until heap is empty)
   
   - Append current sum to result

3. **Return** the result array

**Time Complexity**: O(n log n + m*k log n)
- Building heap: O(n log n)
- Each query processes up to k elements with heap operations: O(k log n)
- Total: O(n log n + m*k log n)

**Space Complexity**: O(n)
- Heap stores n elements: O(n)
- Marked set stores up to n indices: O(n)

**Code**:
```python
import heapq

class Solution:
    def unmarkedSumArray(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        pq = []  # Min-heap: (value, index)
        marked = set()
        s = sum(nums)
        res = []

        # Build heap with all elements
        for i, val in enumerate(nums):
            heapq.heappush(pq, (val, i))
        
        # Process each query
        for idx, k in queries:
            # Step 1: Mark element at index idx
            if idx not in marked:
                marked.add(idx)
                s -= nums[idx]
            
            # Step 2: Mark k smallest unmarked elements
            for _ in range(k):
                # Lazy deletion: skip already marked elements
                while pq and pq[0][1] in marked:
                    heapq.heappop(pq)
                
                # Mark the smallest unmarked element
                if pq:
                    val, i = heapq.heappop(pq)
                    marked.add(i)
                    s -= nums[i]
            
            res.append(s)
        
        return res
```

**Why this works**:
- The heap automatically maintains elements sorted by (value, index)
- Lazy deletion ensures we always get the smallest unmarked element
- The running sum approach avoids recalculating sums after each query
- The set provides O(1) lookups for marked status

# Tags
`Array` `Heap (Priority Queue)` `Simulation` `Greedy`

