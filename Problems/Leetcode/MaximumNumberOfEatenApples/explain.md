## Problem

https://leetcode.com/problems/maximum-number-of-eaten-apples/

```
There is a special kind of apple tree that grows apples every day for n days. 
On the ith day, the tree grows apples[i] apples that will rot after days[i] days, 
that is on day i + days[i] the apples will be rotten and cannot be eaten. 
On some days, the apple tree does not grow any apples, which are denoted by 
apples[i] == 0 and days[i] == 0.

You decided to eat at most one apple a day (to keep the doctors away). 
Note that you can keep eating after the first n days.

Given two integer arrays days and apples of length n, return the maximum number 
of apples you can eat.

Example 1:
Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
Output: 7

Example 2:
Input: apples = [3,0,0,0,0,2], days = [3,0,0,0,0,2]
Output: 5

Constraints:
- n == apples.length == days.length
- 1 <= n <= 2 * 10^4
- 0 <= apples[i], days[i] <= 2 * 10^4
- days[i] = 0 if and only if apples[i] = 0
```

## Observations

1. **Greedy Strategy**: To maximize eaten apples, we should always eat the apples that will rot soonest (earliest expiration date). This prevents waste from rotting.

2. **Two Phases**: 
   - Phase 1 (days 0 to n-1): New apples grow each day while we eat existing apples
   - Phase 2 (days n onwards): No new apples grow, but we continue eating remaining apples

3. **Priority Queue**: A min-heap is ideal for efficiently tracking and retrieving apples by their rot date. Always pop the batch with the earliest rot date.

4. **Cleanup**: On each day, remove all rotten apple batches (where rot_day <= current_day) before eating.

5. **One Apple Per Day**: We can only eat one apple per day, so we decrement the count of the chosen batch and re-insert if apples remain.

## Solution

**Approach: Greedy with Min-Heap**

```python
import heapq

class Solution:
    def eatenApples(self, apples: List[int], days: List[int]) -> int:
        n = len(apples)
        pq = []  # min-heap: (rot_day, num_apples)
        res = 0
        
        # Phase 1: Process days 0 to n-1 (while apples are growing)
        for i in range(n):
            # Add new apples grown on day i
            if apples[i] > 0 and days[i] > 0:
                heapq.heappush(pq, (i + days[i], apples[i]))
            
            # Remove all rotten apples
            while pq and pq[0][0] <= i:
                heapq.heappop(pq)
            
            # Eat one apple from the batch that rots soonest
            if pq:
                rot_day, apple = heapq.heappop(pq)
                apple -= 1
                res += 1
                # Re-add batch if apples remain
                if apple > 0:
                    heapq.heappush(pq, (rot_day, apple))
        
        # Phase 2: Continue eating after growth period
        cur_day = n - 1
        while pq:
            cur_day += 1
            
            # Remove all rotten apples
            while pq and pq[0][0] <= cur_day:
                heapq.heappop(pq)
            
            # Eat one apple from the batch that rots soonest
            if pq:
                rot_day, apple = heapq.heappop(pq)
                apple -= 1
                res += 1
                # Re-add batch if apples remain
                if apple > 0:
                    heapq.heappush(pq, (rot_day, apple))
        
        return res
```

**Complexity Analysis:**
- Time: O(n log n) where n is the length of apples array. Each heap operation is O(log n) and we do at most O(n) operations.
- Space: O(n) for the priority queue to store apple batches.

**Key Insight:** The greedy approach works because eating apples with earlier expiration dates never makes the solution worse - it only prevents waste and preserves optionality for future days.

# Tags
`Heap` `Priority Queue` `Greedy` `Array` `Simulation`

