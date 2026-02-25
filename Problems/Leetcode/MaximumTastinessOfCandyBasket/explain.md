## Problem

https://leetcode.com/problems/maximum-tastiness-of-candy-basket/

```
You are given an array of positive integers price where price[i] denotes the price of the ith candy and a positive integer k.

The store sells baskets of k distinct candies. The tastiness of a candy basket is the smallest absolute difference of the prices of any two candies in the basket.

Return the maximum tastiness of a candy basket.

Example 1:
Input: price = [13,5,1,8,21,2], k = 3
Output: 8
Explanation: Choose the candies with the prices [13,5,21].
The tastiness of the candy basket is: min(|13 - 5|, |13 - 21|, |5 - 21|) = min(8, 8, 16) = 8.

Example 2:
Input: price = [1,3,1], k = 2
Output: 2

Example 3:
Input: price = [7,7,7,7], k = 2
Output: 0

Constraints:
- 2 <= k <= price.length <= 10^5
- 1 <= price[i] <= 10^9
```

## Observations

1. **Tastiness Definition**: The tastiness is the minimum absolute difference between any two candy prices in the basket. We want to maximize this minimum difference.

2. **Key Insight**: This is a **binary search on answer** problem. Instead of trying all possible combinations of k candies, we can binary search on the possible tastiness values.

3. **Monotonicity**: If we can form a basket with tastiness `x`, we can also form a basket with tastiness `x-1`. This monotonic property allows us to use binary search.

4. **Greedy Selection**: For a given target tastiness `t`, we can greedily check if it's possible to select k candies:
   - Sort the prices
   - Start with the first candy
   - Keep selecting candies that are at least `t` distance apart
   - If we can select k candies this way, then tastiness `t` is achievable

5. **Search Space**: 
   - Minimum possible tastiness: 0 (when all selected candies have the same price)
   - Maximum possible tastiness: `max(price) - min(price)`

## Solution

### Approach: Binary Search on Answer

**Algorithm:**
1. Sort the price array to make greedy selection possible
2. Binary search on the tastiness value from 0 to `price[-1] - price[0]`
3. For each mid value, check if it's possible to select k candies with at least mid distance between consecutive prices
4. If possible, try to find a larger tastiness (search right half)
5. If not possible, search left half
6. Return the maximum feasible tastiness

**Time Complexity:** O(n log n + n log(max_price - min_price))
- Sorting: O(n log n)
- Binary search: O(log(max_price - min_price))
- Each check: O(n)

**Space Complexity:** O(1) or O(n) depending on sorting implementation

```python
class Solution:
    def maximumTastiness(self, price: List[int], k: int) -> int:
        price.sort()
        n = len(price)

        def check_possible(max_diff: int) -> bool:
            """Check if we can select k candies with at least max_diff distance"""
            count = 1  # Start with the first candy
            prev = price[0]
            for val in price:
                if val - prev >= max_diff:
                    count += 1
                    prev = val
            return count >= k

        left = 0
        right = price[-1] - price[0]
        res = 0
        
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid  # Found a valid tastiness, try to maximize
                left = mid + 1
            else:
                right = mid - 1
        
        return res
```

**Example Walkthrough (price = [13,5,1,8,21,2], k = 3):**
1. Sort: [1,2,5,8,13,21]
2. Binary search range: [0, 20]
3. Try mid = 10: Can we select 3 candies with diff >= 10?
   - Start with 1, next >= 11 is 13, next >= 23 doesn't exist
   - Count = 2 < 3, so mid = 10 is too large
4. Try mid = 5: [1, 8, 13] or [1, 8, 21] - possible! Try larger.
5. Try mid = 8: [1, 13, 21] - possible! Minimum diff = 8
6. Try mid = 9: Can't select 3 candies with diff >= 9
7. Answer: 8

# Tags
`Binary Search` `Array` `Greedy` `Sorting` `Binary Search on Answer`

