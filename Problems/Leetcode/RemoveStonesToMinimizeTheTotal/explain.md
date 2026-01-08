## Problem

https://leetcode.com/problems/remove-stones-to-minimize-the-total/description/

```
You are given a 0-indexed integer array piles, where piles[i] represents the number of stones 
in the ith pile, and an integer k. You should apply the following operation exactly k times:

- Choose any piles[i] and remove floor(piles[i] / 2) stones from it.
- Notice that you can apply the operation on the same pile more than once.

Return the minimum possible total number of stones remaining after applying the k operations.

floor(x) is the largest integer that is smaller than or equal to x (i.e., rounds x down).

Example 1:
Input: piles = [5,4,9], k = 2
Output: 12
Explanation: Steps of a possible scenario are:
- Apply the operation on pile 2. The resulting piles are [5,4,5].
- Apply the operation on pile 0. The resulting piles are [3,4,5].
The total number of stones in [3,4,5] is 12.

Example 2:
Input: piles = [4,3,6,7], k = 3
Output: 12
Explanation: Steps of a possible scenario are:
- Apply the operation on pile 2. The resulting piles are [4,3,3,7].
- Apply the operation on pile 3. The resulting piles are [4,3,3,4].
- Apply the operation on pile 0. The resulting piles are [2,3,3,4].
The total number of stones in [2,3,3,4] is 12.

Constraints:
- 1 <= piles.length <= 10^5
- 1 <= piles[i] <= 10^4
- 1 <= k <= 10^5
```

## Observations

1. **Greedy Strategy**: To minimize the total stones remaining, we should always remove stones from the **largest pile**. This is because removing half of a larger pile reduces the total more than removing half of a smaller pile.

2. **Dynamic Nature**: After removing stones from a pile, its size changes, so we need to continually track which pile is the largest after each operation.

3. **Max-Heap Structure**: A max-heap (priority queue) is perfect for this problem because:
   - It allows us to efficiently get the maximum element in O(log n)
   - After removing stones, we can re-insert the updated pile in O(log n)
   - We perform k operations, each costing O(log n)

4. **Floor Division**: When we remove floor(piles[i] / 2) stones, we're keeping ceil(piles[i] / 2) stones.
   - For even numbers: removing 6/2 = 3, leaving 3
   - For odd numbers: removing 5/2 = 2 (floor), leaving 3
   - This can be computed as: `val - (val >> 1)` where `>>` is right bit shift (integer division by 2)

5. **Python's heapq**: Python only provides min-heap, so we negate values to simulate a max-heap.

## Solution

### Approach: Greedy with Max-Heap (Priority Queue)

**Algorithm:**
1. Build a max-heap from all pile values (negate them for Python's min-heap)
2. Repeat k times:
   - Extract the maximum pile
   - Calculate stones to remove: floor(pile / 2)
   - Calculate remaining stones: pile - floor(pile / 2)
   - Push the updated pile back to the heap
3. Return the sum of all remaining stones

**Why This Works:**
- At each step, removing stones from the largest pile gives us the maximum reduction
- The greedy choice is optimal because we want to minimize the total
- Even if a pile becomes smaller after an operation, we dynamically adjust by always picking the current largest

**Implementation:**

```python
import heapq

class Solution:
    def minStoneSum(self, piles: List[int], k: int) -> int:
        # Create a max-heap by negating all values
        pq = []
        for val in piles:
            heapq.heappush(pq, -val)
        
        # Perform k operations
        while pq and k:
            # Extract max (most negative value)
            val = heapq.heappop(pq)
            val *= -1  # Convert back to positive
            
            # Calculate stones to remove: floor(val / 2)
            removed = val >> 1  # Bit shift right = divide by 2 (floor)
            
            # Push updated pile back (remaining stones)
            heapq.heappush(pq, -(val - removed))
            k -= 1
        
        # Sum all remaining stones (negate back to positive)
        return -sum(pq)
```

**Time Complexity:** O(n + k log n)
- Building the heap: O(n) where n is the number of piles
- Each of k operations: O(log n) for pop and push
- Final sum: O(n)
- Total: O(n + k log n)

**Space Complexity:** O(n)
- The heap stores all n piles

**Alternative Bit Manipulation Insights:**
- `val >> 1` is equivalent to `val // 2` (floor division by 2)
- `val - (val >> 1)` gives us the remaining stones after removing half
- For val = 5: remaining = 5 - 2 = 3
- For val = 6: remaining = 6 - 3 = 3

# Tags

Heap, Priority Queue, Greedy, Array

