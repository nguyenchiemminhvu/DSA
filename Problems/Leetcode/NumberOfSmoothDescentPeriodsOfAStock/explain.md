## Problem

https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/description/

You are given an integer array `prices` representing the daily price history of a stock, where `prices[i]` is the stock price on the ith day.

A **smooth descent period** of a stock consists of one or more contiguous days such that the price on each day is lower than the price on the preceding day by exactly 1. The first day of the period is exempted from this rule.

Return the number of smooth descent periods.

**Example 1:**
```
Input: prices = [3,2,1,4]
Output: 7
Explanation: There are 7 smooth descent periods:
[3], [2], [1], [4], [3,2], [2,1], and [3,2,1]
Note that a period with one day is a smooth descent period by the definition.
```

**Example 2:**
```
Input: prices = [8,6,7,7]
Output: 4
Explanation: There are 4 smooth descent periods: [8], [6], [7], and [7]
Note that [8,6] is not a smooth descent period as 8 - 6 ≠ 1.
```

**Example 3:**
```
Input: prices = [1]
Output: 1
Explanation: There is 1 smooth descent period: [1]
```

**Constraints:**
- 1 <= prices.length <= 10^5
- 1 <= prices[i] <= 10^5

## Observations

1. **Single element is always valid**: Every single day forms a smooth descent period by itself.

2. **Contiguous descent pattern**: A smooth descent requires `prices[i] = prices[i-1] - 1` for consecutive days.

3. **Counting subarrays**: For a continuous descent sequence of length `k`, the number of subarrays is:
   - Length 1: k subarrays
   - Length 2: k-1 subarrays
   - Length 3: k-2 subarrays
   - ...
   - Length k: 1 subarray
   - **Total**: `k * (k + 1) / 2`

4. **Dynamic Programming approach**: For each position, we can track how many smooth descent periods end at that position.

5. **Two-pointer technique**: We can use a sliding window to identify continuous descent sequences.

## Solution

### Approach: Dynamic Programming with Two Pointers

**Key Idea:**
- Use a DP array where `dp[i]` represents the number of smooth descent periods ending at index `i`.
- For each position, if it continues the descent pattern, it contributes all previous periods plus new ones.
- When a position `i` continues the descent from position `i-1`:
  - All periods ending at `i-1` can be extended to include `i`
  - Plus one new period starting at the beginning of the current descent sequence

**Algorithm:**
1. Initialize `dp` array with all 1s (each element forms a single-element period)
2. Use two pointers `left` and `right` to track continuous descent sequences
3. When `prices[right] + 1 == prices[right-1]` (descent continues):
   - Add the count of new periods: `dp[right] += right - left`
   - This adds all periods that can end at position `right`
4. When descent breaks, move `left` to `right`
5. Sum all values in `dp` array

```python
class Solution:
    def getDescentPeriods(self, prices: List[int]) -> int:
        n = len(prices)
        dp = [1] * n  # Each element is a period by itself
        left = 0
        right = 1
        
        while right < n:
            # Find continuous descent sequence
            while right < n and prices[right] + 1 == prices[right - 1]:
                # Add number of new periods ending at right
                dp[right] += right - left
                right += 1
            # Reset left pointer when descent breaks
            left = right
            right += 1
        
        return sum(dp)
```

**Time Complexity**: O(n) - Single pass through the array
**Space Complexity**: O(n) - For the DP array

**Example Walkthrough** for `[3,2,1,4]`:
- Initial: `dp = [1,1,1,1]`, `left=0, right=1`
- At index 1: `2+1=3` ✓, `dp[1] += 1-0 = 2`, `dp = [1,2,1,1]`
- At index 2: `1+1=2` ✓, `dp[2] += 2-0 = 3`, `dp = [1,2,3,1]`
- At index 3: `4+1≠1` ✗, reset `left=3`
- Result: `sum([1,2,3,1]) = 7`

## Alternatives

### Alternative 1: Space-Optimized Sliding Window

Instead of maintaining a DP array, we can calculate the count on-the-fly.

```python
class Solution:
    def getDescentPeriods(self, prices: List[int]) -> int:
        n = len(prices)
        result = 0
        length = 1  # Length of current descent sequence
        
        for i in range(n):
            if i > 0 and prices[i] + 1 == prices[i - 1]:
                length += 1
            else:
                length = 1
            
            # Add all periods ending at position i
            result += length
        
        return result
```

**Time Complexity**: O(n)
**Space Complexity**: O(1) - Only using a few variables

**Explanation:**
- `length` tracks the current descent sequence length
- For each position, `length` represents how many periods end at that position
- When descent continues, increment `length`; otherwise reset to 1

### Alternative 2: Mathematical Formula for Sequences

Find all continuous descent sequences and apply the arithmetic sum formula.

```python
class Solution:
    def getDescentPeriods(self, prices: List[int]) -> int:
        n = len(prices)
        result = 0
        i = 0
        
        while i < n:
            j = i
            # Find end of current descent sequence
            while j + 1 < n and prices[j + 1] + 1 == prices[j]:
                j += 1
            
            # Length of descent sequence
            length = j - i + 1
            # Apply formula: k * (k + 1) / 2
            result += length * (length + 1) // 2
            
            i = j + 1
        
        return result
```

**Time Complexity**: O(n)
**Space Complexity**: O(1)

**Explanation:**
- Find each maximal descent sequence
- For a sequence of length `k`, the number of subarrays is `k*(k+1)/2`
- Sum up contributions from all sequences

### Comparison of Approaches

| Approach | Time | Space | Readability | Notes |
|----------|------|-------|-------------|-------|
| DP with Two Pointers | O(n) | O(n) | Medium | Original solution, clear DP logic |
| Space-Optimized | O(n) | O(1) | High | **Most efficient**, easy to understand |
| Mathematical Formula | O(n) | O(1) | Medium | Elegant, uses arithmetic series formula |

**Recommended**: The **Space-Optimized Sliding Window** approach is the best choice - it's efficient, uses constant space, and is easy to understand.

# Tags

`Array` `Dynamic Programming` `Sliding Window` `Two Pointers` `Math`

