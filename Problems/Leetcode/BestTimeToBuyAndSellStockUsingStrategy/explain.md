## Problem

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy/description/

## Problem

You are given two integer arrays `prices` and `strategy`, where:
- `prices[i]` is the price of a given stock on the ith day.
- `strategy[i]` represents a trading action on the ith day:
  - `-1` indicates buying one unit of the stock
  - `0` indicates holding the stock
  - `1` indicates selling one unit of the stock

You are also given an even integer `k`, and may perform **at most one modification** to the strategy. A modification consists of:
1. Selecting exactly `k` consecutive elements in strategy
2. Set the first `k / 2` elements to `0` (hold)
3. Set the last `k / 2` elements to `1` (sell)

The **profit** is defined as the sum of `strategy[i] * prices[i]` across all days.

**Return the maximum possible profit you can achieve.**

**Note:** There are no constraints on budget or stock ownership, so all buy and sell operations are feasible regardless of past actions.

### Examples

**Example 1:**
```
Input: prices = [4,2,8], strategy = [-1,0,1], k = 2
Output: 10

Explanation:
Modification          Strategy        Profit Calculation                      Profit
Original              [-1, 0, 1]      (-1 × 4) + (0 × 2) + (1 × 8) = 4        4
Modify [0, 1]         [0, 1, 1]       (0 × 4) + (1 × 2) + (1 × 8) = 10        10 ✓
Modify [1, 2]         [-1, 0, 1]      (-1 × 4) + (0 × 2) + (1 × 8) = 4        4
```

**Example 2:**
```
Input: prices = [5,4,3], strategy = [1,1,0], k = 2
Output: 9

Explanation:
The original strategy gives 9, which is already optimal.
Any modification would only decrease the profit.
```

### Constraints
- `2 <= prices.length == strategy.length <= 10^5`
- `1 <= prices[i] <= 10^5`
- `-1 <= strategy[i] <= 1`
- `2 <= k <= prices.length`
- `k` is even

---

## Observations

1. **Original Profit Calculation**: First calculate the profit without any modification as a baseline.

2. **Understanding the Modification**: 
   - We select `k` consecutive elements starting at index `i`
   - First `k/2` elements become `0` (hold) → change from `strategy[j]` to `0`
   - Last `k/2` elements become `1` (sell) → change from `strategy[j]` to `1`

3. **Delta Calculation**:
   - **Left side**: `k/2` elements that change to `0`
     - If original value is `-1`: loses `-1 × price = -price` profit, gains `0`
     - Change in profit: `0 - (-price) = +price`
     - General delta: `-(strategy[j] × prices[j])`
   
   - **Right side**: `k/2` elements that change to `1`
     - If original value is `0`: loses `0 × price = 0` profit, gains `1 × price = price`
     - Change in profit: `price - 0 = +price`
     - General delta: `(1 - strategy[j]) × prices[j]`

4. **Sliding Window Optimization**:
   - We need to check all possible starting positions for the k-window
   - This is `n - k + 1` positions
   - Instead of recalculating the entire delta for each position, use a sliding window
   - When moving the window from position `i-1` to position `i`:
     - Remove contribution from `i-1` on the left side
     - Add contribution from `i + half - 1` on the left side
     - Remove contribution from `i + half - 1` on the right side
     - Add contribution from `i + k - 1` on the right side

5. **Final Answer**:
   - Either keep the original strategy (no modification): `base_profit`
   - Or apply the best modification found: `base_profit + best_delta`
   - We take the maximum of these, which means we use `max(0, best_delta)` to handle negative deltas

---

## Solution Approach

### Algorithm: Sliding Window with Delta Tracking

**Time Complexity**: O(n) where n is the length of prices/strategy
**Space Complexity**: O(1) excluding the output

### Step-by-Step Explanation

```python
class Solution:
    def maxProfit(self, prices: List[int], strategy: List[int], k: int) -> int:
        n = len(prices)
        half = k // 2

        # Step 1: Calculate base profit without any modification
        base_profit = sum(prices[i] * strategy[i] for i in range(n))

        # Step 2: Initialize the sliding window for the first k-window
        # Left side: profit change if first half elements become 0
        left = 0
        for i in range(half):
            left += -(prices[i] * strategy[i])
        
        # Right side: profit change if second half elements become 1
        right = 0
        for i in range(half, k):
            right += prices[i] * (1 - strategy[i])
        
        # Track the best delta found so far
        best_delta = left + right

        # Step 3: Slide the window through all valid positions
        for i in range(1, n - k + 1):
            # Remove the leftmost element of the previous left window
            left -= -(prices[i - 1] * strategy[i - 1])
            # Add the new element entering the left window
            left += -(prices[i + half - 1] * strategy[i + half - 1])

            # Remove the leftmost element of the previous right window
            right -= prices[i + half - 1] * (1 - strategy[i + half - 1])
            # Add the new element entering the right window
            right += prices[i + k - 1] * (1 - strategy[i + k - 1])

            # Update the best delta
            best_delta = max(best_delta, left + right)
        
        # Step 4: Return base profit plus the best improvement (or 0 if no improvement)
        return base_profit + max(0, best_delta)
```

### Detailed Trace (Example 1)

**Input**: `prices = [4,2,8]`, `strategy = [-1,0,1]`, `k = 2`
- `n = 3`, `half = 1`
- `base_profit = (-1×4) + (0×2) + (1×8) = 4`

**Initial window [0, 1]**:
- `left = -((-1) × 4) = 4`
- `right = (1 - 0) × 2 = 2`
- `best_delta = 4 + 2 = 6`

**Slide to window [1, 2]**:
- `left` updates: remove i=0, add i=1
  - `left -= -((-1) × 4) = 4 - 4 = 0`
  - `left += -(0 × 2) = 0 + 0 = 0`
- `right` updates: remove i=1, add i=2
  - `right -= (1 - 0) × 2 = 2 - 2 = 0`
  - `right += (1 - 1) × 8 = 0 + 0 = 0`
- `best_delta = max(6, 0) = 6`

**Result**: `base_profit + max(0, best_delta) = 4 + 6 = 10` ✓

### Why This Works

1. **Correctness**: We check all `n - k + 1` possible windows and track the maximum profit improvement from any modification.

2. **Efficiency**: The sliding window prevents redundant recalculations. Each position's contribution is calculated only once as it enters and once as it leaves the window.

3. **Edge Case Handling**: By taking `max(0, best_delta)`, we implicitly handle the case where no modification is beneficial—we simply don't apply any modification.

---

## Tags
- `Sliding Window`
- `Array`
- `Dynamic Programming`
- `Optimization`
s