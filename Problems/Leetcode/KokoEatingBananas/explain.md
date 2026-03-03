## Problem

https://leetcode.com/problems/koko-eating-bananas/description/

Koko loves to eat bananas. There are `n` piles of bananas, the `i-th` pile has `piles[i]` bananas. The guards have gone and will come back in `h` hours.

Koko can decide her bananas-per-hour eating speed of `k`. Each hour, she chooses some pile of bananas and eats `k` bananas from that pile. If the pile has less than `k` bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer `k` such that she can eat all the bananas within `h` hours.

**Example 1:**
- Input: piles = [3,6,7,11], h = 8
- Output: 4

**Example 2:**
- Input: piles = [30,11,23,4,20], h = 5
- Output: 30

**Example 3:**
- Input: piles = [30,11,23,4,20], h = 6
- Output: 23

**Constraints:**
- 1 <= piles.length <= 10^4
- piles.length <= h <= 10^9
- 1 <= piles[i] <= 10^9

## Observations

1. **Search Space Identification**: The eating speed `k` must be at least 1 (minimum) and at most `max(piles)` (eating the largest pile in one hour). We need to find the minimum `k` in this range.

2. **Monotonic Property**: If Koko can finish all bananas with speed `k`, she can definitely finish with any speed greater than `k`. Conversely, if she cannot finish with speed `k`, she cannot finish with any speed less than `k`. This monotonic property makes binary search applicable.

3. **Time Calculation**: For each pile with `p` bananas and eating speed `k`:
   - If `p <= k`: takes 1 hour
   - If `p > k`: takes `ceil(p/k) = (p + k - 1) // k` hours

4. **Feasibility Check**: For a given speed `k`, we can calculate the total hours needed. If `total_hours <= h`, the speed is feasible.

5. **Binary Search Target**: We want the leftmost (minimum) `k` where the feasibility check passes.

## Solution

```python
class Solution:
    def minEatingSpeed(self, nums: List[int], h: int) -> int:
        n = len(nums)

        def check_possible(k: int) -> bool:
            total_h = 0
            for val in nums:
                if val <= k:
                    total_h += 1
                else:
                    total_h += (val + k - 1) // k
            return total_h <= h

        left = 1
        right = sum(nums)
        k = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                k = mid
                right = mid - 1
            else:
                left = mid + 1
        return k
```

**Algorithm Explanation:**

1. **Binary Search Setup**: 
   - `left = 1`: minimum possible eating speed
   - `right = sum(nums)`: upper bound (though `max(nums)` would be more optimal)
   - `k = right`: stores the current best answer

2. **check_possible(k)**: Calculates total hours needed to eat all bananas at speed `k`:
   - For each pile, compute hours using ceiling division: `(val + k - 1) // k`
   - Returns `True` if total hours ≤ `h`

3. **Binary Search Logic**:
   - If current speed `mid` is feasible, record it as a potential answer and try smaller speeds (`right = mid - 1`)
   - If not feasible, we need faster speed (`left = mid + 1`)

4. **Time Complexity**: O(n × log(sum(piles))) where n is the number of piles
5. **Space Complexity**: O(1)

**Note**: The upper bound could be optimized to `max(nums)` instead of `sum(nums)` since eating at speed `max(nums)` guarantees finishing each pile in at most 1 hour.

# Tags

- Binary Search
- Array

