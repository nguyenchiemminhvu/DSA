## Problem

https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/description/

```
You are given an array nums consisting of positive integers.

Starting with score = 0, apply the following algorithm:

1. Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
2. Add the value of the chosen integer to score.
3. Mark the chosen element and its two adjacent elements if they exist.
4. Repeat until all the array elements are marked.

Return the score you get after applying the above algorithm.

Example 1:
Input: nums = [2,1,3,4,5,2]
Output: 7
Explanation: We mark the elements as follows:
- 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
- 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
- 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
Our score is 1 + 2 + 4 = 7.

Example 2:
Input: nums = [2,3,5,1,3,2]
Output: 5
Explanation: We mark the elements as follows:
- 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,3,5,1,3,2].
- 2 is the smallest unmarked element, since there are two of them, we choose the left-most one, 
  so we mark the one at index 0 and its right adjacent element: [2,3,5,1,3,2].
- 2 is the only remaining unmarked element, so we mark it: [2,3,5,1,3,2].
Our score is 1 + 2 + 2 = 5.

Constraints:
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^6
```

## Observations

1. **Greedy Approach**: We always need to select the smallest unmarked element, which suggests a greedy algorithm.

2. **Index Tracking**: When there are ties (multiple elements with the same value), we must choose the one with the smallest index. This means we need to track both values and their original indices.

3. **Marking Strategy**: After selecting an element, we mark it along with its adjacent neighbors (i-1 and i+1). This prevents them from being selected in future iterations.

4. **Data Structure Choice**: A min-heap (priority queue) is ideal because:
   - It efficiently retrieves the smallest element in O(log n) time
   - We can store tuples of (value, index) to handle tie-breaking by index automatically
   - Python's heapq naturally sorts tuples by first element, then by second element

5. **Marked Elements**: We need a way to track which indices have been marked. A set is perfect for O(1) lookup time.

## Solution

```python
import heapq
class Solution:
    def findScore(self, nums: List[int]) -> int:
        res = 0
        pq = []
        
        # Build min-heap with (value, index) pairs
        for i, val in enumerate(nums):
            heapq.heappush(pq, (val, i))
        
        marked = set()
        
        # Process elements in order of smallest value (and smallest index for ties)
        while pq:
            val, i = heapq.heappop(pq)
            
            # Skip if this index is already marked
            if i not in marked:
                res += val
                # Mark current element and its neighbors
                marked.add(i)
                marked.add(i - 1)
                marked.add(i + 1)
        
        return res
```

**Algorithm Explanation:**

1. **Initialization** (O(n log n)):
   - Create a min-heap containing tuples of (value, index) for all elements
   - Initialize an empty set to track marked indices
   - Initialize result score to 0

2. **Processing Loop** (O(n log n)):
   - Extract the minimum element from the heap
   - If its index is not marked:
     - Add its value to the result score
     - Mark the current index and its two adjacent indices (i-1, i+1)
   - Continue until heap is empty

3. **Time Complexity**: O(n log n)
   - Building the heap: O(n log n)
   - Processing n elements with heap operations: O(n log n)

4. **Space Complexity**: O(n)
   - Heap storage: O(n)
   - Marked set: O(n)

**Key Insights:**
- The heap automatically handles tie-breaking by index since tuples are compared element-by-element
- Adding indices i-1 and i+1 to the marked set is safe even if they're out of bounds (they simply won't match any valid index)
- We don't need to explicitly check if neighbors exist before marking them

# Tags
`Greedy` `Heap` `Priority Queue` `Array` `Sorting` `Simulation`

