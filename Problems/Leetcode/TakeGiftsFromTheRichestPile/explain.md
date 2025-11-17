## Problem

https://leetcode.com/problems/take-gifts-from-the-richest-pile/description/

```
You are given an integer array gifts denoting the number of gifts in various piles. Every second, you do the following:

Choose the pile with the maximum number of gifts.
If there is more than one pile with the maximum number of gifts, choose any.
Reduce the number of gifts in the pile to the floor of the square root of the original number of gifts in the pile.
Return the number of gifts remaining after k seconds.

Example 1:

Input: gifts = [25,64,9,4,100], k = 4
Output: 29
Explanation: 
The gifts are taken in the following way:
- In the first second, the last pile is chosen and 10 gifts are left behind.
- Then the second pile is chosen and 8 gifts are left behind.
- After that the first pile is chosen and 5 gifts are left behind.
- Finally, the last pile is chosen again and 3 gifts are left behind.
The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.

Example 2:

Input: gifts = [1,1,1,1], k = 4
Output: 4
Explanation: 
In this case, regardless which pile you choose, you have to leave behind 1 gift in each pile. 
That is, you can't take any pile with you. 
So, the total gifts remaining are 4.

Constraints:

1 <= gifts.length <= 103
1 <= gifts[i] <= 109
1 <= k <= 103
```

## Observations

1. **Core Pattern**: We need to repeatedly find the maximum element and reduce it to floor(sqrt(value))
2. **Data Structure Choice**: This is a classic max-heap problem since we need to efficiently:
   - Find the maximum element (O(1))
   - Remove the maximum element (O(log n))
   - Insert the reduced value back (O(log n))
3. **Python heapq limitation**: Python's `heapq` only provides min-heap, so we use negative values to simulate max-heap
4. **Mathematical insight**: floor(sqrt(x)) significantly reduces large numbers but has minimal effect on small numbers
5. **Termination conditions**: 
   - We perform exactly k operations (if heap is not empty)
   - If heap becomes empty before k operations (edge case)
6. **Time complexity**: O(k log n) where n is the length of gifts array
7. **Space complexity**: O(n) for the heap

## Solution

```python
import heapq
import math

class Solution:
    def pickGifts(self, gifts: List[int], k: int) -> int:
        # Step 1: Build max-heap using negative values (Python heapq is min-heap)
        pq = []
        for val in gifts:
            heapq.heappush(pq, -val)
        
        # Step 2: Perform k operations
        while pq and k:
            # Get maximum element (negate to get original positive value)
            val = heapq.heappop(pq)
            val *= -1
            
            # Calculate floor of square root
            remain = math.floor(math.sqrt(val))
            
            # Push back the reduced value (negate for max-heap simulation)
            heapq.heappush(pq, -remain)
            k -= 1

        # Step 3: Sum all remaining gifts (negate to get positive values)
        return sum(-val for val in pq)
```

### Algorithm Walkthrough

**Example: gifts = [25,64,9,4,100], k = 4**

1. **Initial heap**: [-100, -64, -25, -9, -4] (max-heap via negation)
2. **Operation 1**: Remove -100 → sqrt(100) = 10 → Insert -10
   - Heap: [-64, -25, -10, -9, -4]
3. **Operation 2**: Remove -64 → sqrt(64) = 8 → Insert -8
   - Heap: [-25, -10, -9, -8, -4]
4. **Operation 3**: Remove -25 → sqrt(25) = 5 → Insert -5
   - Heap: [-10, -9, -8, -5, -4]
5. **Operation 4**: Remove -10 → sqrt(10) ≈ 3 → Insert -3
   - Final heap: [-9, -8, -5, -4, -3]
6. **Result**: 9 + 8 + 5 + 4 + 3 = 29

### Key Insights

- **Greedy approach works**: Always reducing the largest pile gives optimal result
- **Heap efficiency**: O(log n) operations for each of k iterations
- **Square root effect**: Large numbers reduce significantly (100→10, 64→8), small numbers change minimally (4→2, 1→1)
- **Edge cases handled**: Empty heap check with `while pq and k`

# Tags

- Heap
- Priority Queue
- Greedy
- Math
- Simulation

