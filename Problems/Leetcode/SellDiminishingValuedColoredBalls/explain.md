## Problem

https://leetcode.com/problems/sell-diminishing-valued-colored-balls/description/

```
You have an inventory of different colored balls, and there is a customer that wants orders balls of any color.

The customer weirdly values the colored balls. Each colored ball's value is the number of balls of that color 
you currently have in your inventory. For example, if you own 6 yellow balls, the customer would pay 6 for the 
first yellow ball. After the transaction, there are only 5 yellow balls left, so the next yellow ball is then 
valued at 5 (i.e., the value of the balls decreases as you sell more to the customer).

You are given an integer array, inventory, where inventory[i] represents the number of balls of the ith color 
that you initially own. You are also given an integer orders, which represents the total number of balls that 
the customer wants. You can sell the balls in any order.

Return the maximum total value that you can attain after selling orders colored balls. As the answer may be 
too large, return it modulo 10^9 + 7.

Example 1:
Input: inventory = [2,5], orders = 4
Output: 14
Explanation: Sell the 1st color 1 time (2) and the 2nd color 3 times (5 + 4 + 3).
The maximum total value is 2 + 5 + 4 + 3 = 14.

Example 2:
Input: inventory = [3,5], orders = 6
Output: 19
Explanation: Sell the 1st color 2 times (3 + 2) and the 2nd color 4 times (5 + 4 + 3 + 2).
The maximum total value is 3 + 2 + 5 + 4 + 3 + 2 = 19.

Constraints:
- 1 <= inventory.length <= 10^5
- 1 <= inventory[i] <= 10^9
- 1 <= orders <= min(sum(inventory[i]), 10^9)
```

## Observations

1. **Greedy Strategy**: To maximize profit, we should always sell the most valuable balls first. Since the value of each ball equals the current count of that color, we should prioritize colors with higher counts.

2. **Diminishing Returns**: Each time we sell a ball of a specific color, its value decreases by 1. This creates a natural diminishing returns pattern.

3. **Leveling Strategy**: Instead of selling balls one by one, we can think in terms of "levels":
   - If we have colors with counts [5, 3, 2], we should sell from the highest (5) down to match the next highest (3)
   - This way, we can calculate chunks of sales using arithmetic sums rather than iterating one by one

4. **Arithmetic Sum Formula**: When selling multiple balls from the same color consecutively, we can use the formula:
   - Sum from `lo` to `hi` = (hi + lo) × count / 2
   - This is much more efficient than adding values individually

5. **Edge Cases**:
   - When we can't sell all balls down to the next level, we need to handle partial sales
   - The remainder needs to be distributed across multiple colors at the final level

## Solution

### Approach: Greedy with Level-Based Selling

**Key Idea**: Sort the inventory in descending order and sell balls level by level, processing all colors at the same level together.

**Algorithm Steps**:

1. **Sort**: Sort the inventory in descending order to prioritize highest-value balls.

2. **Process by Levels**:
   - Group colors that have the same current value
   - Determine how many levels we can completely sell from this group
   - Use arithmetic sum to calculate the total value efficiently

3. **Handle Two Cases**:
   - **Case 1 - Full Levels**: If we have enough orders to bring all colors in the current group down to the next level:
     - Calculate the sum of all values from current level to next level for all colors
     - Update remaining orders
   
   - **Case 2 - Partial Level**: If we don't have enough orders to complete the level drop:
     - Sell as many full levels as possible across all colors
     - Distribute the remainder balls at the final level

4. **Modulo Arithmetic**: Apply modulo 10^9 + 7 to prevent overflow.

**Time Complexity**: O(n log n) where n is the length of inventory (dominated by sorting)

**Space Complexity**: O(1) if we don't count the sorting space

### Example Walkthrough

For `inventory = [3,5], orders = 6`:

1. After sorting: `[5, 3]`
2. Start with highest value 5:
   - Current group: 1 color at level 5
   - Next level: 3
   - Can sell: (5-3) × 1 = 2 balls (values: 5, 4)
   - Total so far: 5 + 4 = 9, orders left: 4
3. Now both colors at level 3:
   - Current group: 2 colors at level 3
   - Next level: 0
   - Need to sell 4 balls from 2 colors
   - Full levels: 4 ÷ 2 = 2 levels, remainder = 0
   - Sell down from 3 to 2: (3 + 2) × 2 = 10
4. Total: 9 + 10 = 19

### Code Implementation

```python
from typing import List

class Solution:
    def maxProfit(self, nums: List[int], need: int) -> int:
        MOD = 10**9 + 7
        nums.sort(reverse=True)
        n = len(nums)

        def arith_sum(hi: int, lo: int) -> int:
            """Sum of integers from lo..hi inclusive (lo <= hi)."""
            cnt = hi - lo + 1
            return (hi + lo) * cnt // 2

        res = 0
        i = 0
        count = 0

        while need > 0 and i < n:
            cur_val = nums[i]

            # Find all colors with the same current value
            j = i
            while j < n and nums[j] == cur_val:
                j += 1

            count = j  # number of colors at this level

            next_val = nums[j] if j < n else 0
            diff = cur_val - next_val
            can_sell = diff * count

            if can_sell <= need:
                # Sell all levels from cur_val down to next_val+1
                res += count * arith_sum(cur_val, next_val + 1)
                res %= MOD
                need -= can_sell
                i = j
            else:
                # Partial sale: sell only part of these levels
                full, rem = divmod(need, count)
                low_after_full = cur_val - full

                # Sell 'full' complete levels for each color
                res += count * arith_sum(cur_val, low_after_full + 1)
                res %= MOD

                # Sell 'rem' balls at the final partial level
                res += rem * low_after_full
                res %= MOD
                return res % MOD

        return res % MOD
```

# Tags
`greedy` `sorting` `math` `arithmetic-sum` `medium`

