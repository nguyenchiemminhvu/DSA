## Problem

https://leetcode.com/problems/furthest-building-you-can-reach/description/

```
You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.

You start your journey from building 0 and move to the next building by possibly using bricks or ladders.

While moving from building i to building i+1 (0-indexed),
- If the current building's height is greater than or equal to the next building's height, you do not need a ladder or bricks.
- If the current building's height is less than the next building's height, you can either use one ladder or (h[i+1] - h[i]) bricks.

Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.

Example 1:
Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
Output: 4
Explanation: Starting at building 0, you can follow these steps:
- Go to building 1 without using ladders nor bricks since 4 >= 2.
- Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
- Go to building 3 without using ladders nor bricks since 7 >= 6.
- Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
It is impossible to go beyond building 4 because you do not have any more bricks or ladders.

Example 2:
Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
Output: 7

Example 3:
Input: heights = [14,3,19,3], bricks = 17, ladders = 0
Output: 3

Constraints:
- 1 <= heights.length <= 10^5
- 1 <= heights[i] <= 10^6
- 0 <= bricks <= 10^9
- 0 <= ladders <= heights.length
```

## Observations

1. **Key Insight**: Ladders are more valuable than bricks because one ladder can cover any height difference, while bricks are limited by their count.

2. **Optimal Strategy**: Use bricks first for smaller climbs, and save ladders for the largest climbs. This maximizes our reach.

3. **Greedy Approach**: As we traverse buildings, we should:
   - Initially use bricks for all climbs
   - When we run out of bricks, retroactively replace the largest brick usage with a ladder
   - This ensures ladders are used for the biggest gaps

4. **Data Structure**: A max heap (priority queue) helps us efficiently track and retrieve the largest climbs we've encountered.

## Solution

**Algorithm**:
1. Traverse through buildings from index 1 to n-1
2. For each upward climb (positive height difference):
   - Use bricks first and subtract the difference from brick count
   - Store this climb in a max heap (store as negative to simulate max heap in Python)
   - If bricks become negative (insufficient):
     - If we have ladders available, use one ladder for the largest climb we've made so far
     - Recover those bricks by popping from the heap (the largest climb)
     - If no ladders available, we can't proceed further
3. Return the furthest index reached

**Time Complexity**: O(n log n) where n is the number of buildings
- We iterate through n buildings
- Each heap operation (push/pop) takes O(log n)

**Space Complexity**: O(n) for the heap in worst case

**Implementation**:
```python
import heapq

class Solution:
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
        n = len(heights)
        res = 0
        pq = []  # Max heap to store climbs (stored as negative values)
        
        for i in range(1, n):
            diff = heights[i] - heights[i - 1]
            if diff > 0:  # Need to climb up
                bricks -= diff  # Use bricks first
                heapq.heappush(pq, -diff)  # Store climb in max heap
                
                if bricks < 0:  # Ran out of bricks
                    if ladders == 0:  # No ladders left, can't proceed
                        break
                    ladders -= 1  # Use a ladder
                    bricks += -heapq.heappop(pq)  # Recover bricks from largest climb
            
            res = i  # Update furthest position reached
        
        return res
```

**Why This Works**:
- By using bricks first and then retroactively swapping the largest climbs with ladders, we ensure that our limited ladders are used for the most expensive climbs.
- This greedy approach is optimal because it maximizes the efficiency of our resources.

# Tags
`Greedy` `Heap` `Priority Queue` `Array` `Optimization`

