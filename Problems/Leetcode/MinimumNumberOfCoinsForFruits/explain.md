## Problem

https://leetcode.com/problems/minimum-number-of-coins-for-fruits/description/

```
You are given a 0-indexed integer array prices where prices[i] denotes the number of coins needed to purchase the (i + 1)th fruit.

The fruit market has the following reward for each fruit:
- If you purchase the (i + 1)th fruit at prices[i] coins, you can get any number of the next i fruits for free.

Note that even if you can take fruit j for free, you can still purchase it for prices[j - 1] coins to receive its reward.

Return the minimum number of coins needed to acquire all the fruits.

Example 1:
Input: prices = [3,1,2]
Output: 4
Explanation:
- Purchase the 1st fruit with prices[0] = 3 coins, you are allowed to take the 2nd fruit for free.
- Purchase the 2nd fruit with prices[1] = 1 coin, you are allowed to take the 3rd fruit for free.
- Take the 3rd fruit for free.

Example 2:
Input: prices = [1,10,1,1]
Output: 2

Example 3:
Input: prices = [26,18,6,12,49,7,45,45]
Output: 39

Constraints:
- 1 <= prices.length <= 1000
- 1 <= prices[i] <= 10^5
```

## Observations

1. **Reward Mechanism**: When you buy fruit at index `i` (1-indexed), you can take the next `i` fruits for free.
   - Buy fruit 1 → get next 1 fruit free
   - Buy fruit 2 → get next 2 fruits free
   - Buy fruit 3 → get next 3 fruits free
   - And so on...

2. **Strategic Purchasing**: Even if a fruit can be taken for free, you might want to purchase it to unlock more free fruits later.

3. **Decision at Each Step**: At each position, you need to decide whether to:
   - Buy the current fruit (pay the price, unlock free fruits)
   - Take it for free (if already covered by a previous purchase)

4. **Overlapping Subproblems**: The minimum cost to acquire all fruits from position `i` onwards depends on the minimum cost from future positions, making this a dynamic programming problem.

5. **State Definition**: `F(i)` = minimum coins needed to acquire all fruits from index `i` to the end (0-indexed).

## Solution

### Approach: Top-Down Dynamic Programming (Memoization)

**Key Insight**: When we buy fruit at index `i`, we pay `prices[i]` and can then take any of the next `i+1` fruits for free. This means we can jump to any position from `i+1` to `i+1+(i+1) = 2i+2`.

**Recurrence Relation**:
```
F(i) = prices[i] + min(F(j) for j in range(i+1, min(n, i+1+(i+1)+1)))
```

Where:
- `i` is the current 0-indexed position
- `prices[i]` is the cost to buy the current fruit
- `i+1` is the 1-indexed fruit number (reward amount)
- We can jump to any position from `i+1` to `i+1+(i+1)` (which is `2i+2`)
- `min(n, i+1+(i+1)+1)` ensures we don't go beyond the array

**Base Case**:
- If `i >= n`, return 0 (no more fruits to acquire)

**Implementation Details**:

```python
from functools import lru_cache

class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        n = len(prices)

        # F(i) -> minimum number of coins needed to acquire all fruits from i to n
        @lru_cache(None)
        def F(i: int) -> int:
            if i >= n:
                return 0
            
            # When buying fruit at index i (0-indexed):
            # - We pay prices[i]
            # - We can get next (i+1) fruits for free (1-indexed fruit number)
            # - So we can jump to any position from i+1 to i+1+(i+1) = 2i+2
            end = min(n, i + (i + 1) + 1)
            return prices[i] + min(F(j) for j in range(i + 1, end + 1))
        
        return F(0)
```

**Time Complexity**: O(n²)
- We have `n` states
- For each state, we check up to `n` next positions
- With memoization, each state is computed once

**Space Complexity**: O(n)
- Memoization cache stores at most `n` states
- Recursion stack depth is O(n)

**Example Walkthrough** (prices = [3,1,2]):
1. `F(0)`: Buy fruit 1 for 3 coins, can get next 1 fruit free
   - Can jump to positions 1 or 2
   - Choose min of: F(1), F(2)
   
2. `F(1)`: Buy fruit 2 for 1 coin, can get next 2 fruits free
   - Can jump to positions 2, 3, or 4
   - F(3) = 0, F(4) = 0
   - Returns 1 + 0 = 1
   
3. `F(2)`: Buy fruit 3 for 2 coins, can get next 3 fruits free
   - Can jump beyond array
   - Returns 2 + 0 = 2
   
4. `F(0)` = 3 + min(F(1), F(2)) = 3 + min(1, 2) = 3 + 1 = 4

# Tags
Dynamic Programming, Memoization, Recursion, Greedy, Array

