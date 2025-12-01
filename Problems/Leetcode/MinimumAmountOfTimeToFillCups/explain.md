## Problem

https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/description/

```
You have a water dispenser that can dispense cold, warm, and hot water. Every second, you can either fill up 2 cups with different types of water, or 1 cup of any type of water.

You are given a 0-indexed integer array amount of length 3 where amount[0], amount[1], and amount[2] denote the number of cold, warm, and hot water cups you need to fill respectively. Return the minimum number of seconds needed to fill up all the cups.

Example 1:
Input: amount = [1,4,2]
Output: 4
Explanation: One way to fill up the cups is:
Second 1: Fill up a cold cup and a warm cup.
Second 2: Fill up a warm cup and a hot cup.
Second 3: Fill up a warm cup and a hot cup.
Second 4: Fill up a warm cup.
It can be proven that 4 is the minimum number of seconds needed.

Example 2:
Input: amount = [5,4,4]
Output: 7
Explanation: One way to fill up the cups is:
Second 1: Fill up a cold cup, and a hot cup.
Second 2: Fill up a cold cup, and a warm cup.
Second 3: Fill up a cold cup, and a warm cup.
Second 4: Fill up a warm cup, and a hot cup.
Second 5: Fill up a cold cup, and a hot cup.
Second 6: Fill up a cold cup, and a warm cup.
Second 7: Fill up a hot cup.

Example 3:
Input: amount = [5,0,0]
Output: 5
Explanation: Every second, we fill up a cold cup.

Constraints:
- amount.length == 3
- 0 <= amount[i] <= 100
```

## Observations

1. **Key Insight**: We can fill 2 cups per second if they are of different types, or 1 cup per second if only one type remains.

2. **Greedy Strategy**: To minimize time, we should always fill the two types with the most remaining cups whenever possible. This ensures we maximize the use of the "2 cups per second" capability.

3. **Edge Cases**:
   - If one type has more cups than the sum of the other two, we can't always fill 2 per second
   - If all cups can be paired up, the answer is `(total + 1) / 2`
   - If one type dominates, the answer is `max(amount)`

4. **Mathematical Formula**: The answer is `max(max(amount), (sum(amount) + 1) / 2)`
   - If the largest value ≥ sum of the other two, we need `max(amount)` seconds (the largest value determines the time)
   - Otherwise, we can keep pairing, so we need `ceil(total / 2)` = `(total + 1) / 2` seconds

## Solution

### Approach 1: Greedy with Max Heap (Simulation)

```python
import heapq

class Solution:
    def fillCups(self, amount: List[int]) -> int:
        res = 0
        pq = []
        # Use max heap (negate values since Python has min heap)
        for val in amount:
            if val:
                heapq.heappush(pq, -val)
        
        while pq:
            # Take the type with most cups
            val = heapq.heappop(pq)
            val *= -1  # Convert back to positive
            
            # If there's another type available, fill both
            if pq:
                valval = heapq.heappop(pq)
                valval *= -1
                valval -= 1
                if valval > 0:
                    heapq.heappush(pq, -valval)
            
            # Decrease the first type
            val -= 1
            if val > 0:
                heapq.heappush(pq, -val)
            
            res += 1
        
        return res
```

**Time Complexity**: O(n log 3) where n is the sum of all amounts. Since we have only 3 types, this is effectively O(n).

**Space Complexity**: O(1) - the heap contains at most 3 elements.

**How it works**:
1. Push all non-zero amounts into a max heap (negated for Python's min heap)
2. Each second, greedily pick the two largest amounts and decrement them
3. If only one type remains, decrement just that one
4. Continue until all cups are filled

### Approach 2: Mathematical Formula (Optimal)

```python
class Solution:
    def fillCups(self, amount: List[int]) -> int:
        return max(max(amount), (sum(amount) + 1) // 2)
```

**Time Complexity**: O(1)

**Space Complexity**: O(1)

**Explanation**:
- If the largest amount ≥ sum of the other two, we need at least `max(amount)` seconds (we can't always fill 2 per second)
- Otherwise, we can keep pairing different types, needing `ceil(total / 2)` seconds
- The formula `max(max(amount), (sum(amount) + 1) // 2)` covers both cases

# Tags
#greedy #heap #priority-queue #math #simulation

