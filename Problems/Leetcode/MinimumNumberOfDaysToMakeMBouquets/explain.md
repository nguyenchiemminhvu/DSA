## Problem

https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/description/

You are given an integer array `bloomDay`, an integer `m` and an integer `k`.

You want to make `m` bouquets. To make a bouquet, you need to use `k` **adjacent** flowers from the garden.

The garden consists of `n` flowers, the `i-th` flower will bloom in the `bloomDay[i]` and then can be used in exactly one bouquet.

Return the **minimum number of days** you need to wait to be able to make `m` bouquets from the garden. If it is impossible to make `m` bouquets return `-1`.

**Constraints:**
- `bloomDay.length == n`
- `1 <= n <= 10^5`
- `1 <= bloomDay[i] <= 10^9`
- `1 <= m <= 10^6`
- `1 <= k <= n`

## Observations

1. **Impossibility Check**: If `m * k > n`, it's impossible to make `m` bouquets since we need at least `m * k` flowers total.

2. **Monotonic Property**: If we can make `m` bouquets on day `d`, we can also make `m` bouquets on any day `d' > d` (more flowers will have bloomed). This monotonic property suggests **binary search**.

3. **Search Space**: The answer lies between `1` (minimum bloom day) and `max(bloomDay)` (when all flowers have bloomed).

4. **Feasibility Check**: Given a specific day, we need to check if we can form `m` bouquets, each containing `k` **adjacent** bloomed flowers. A flower is bloomed on day `d` if `bloomDay[i] <= d`.

5. **Greedy Counting**: When checking feasibility, we greedily count consecutive bloomed flowers. Once we reach `k` consecutive flowers, we form a bouquet and reset the counter.

## Solution

**Approach: Binary Search on Answer**

The key insight is that we're searching for the minimum day `d` such that we can make `m` bouquets. Since the feasibility function is monotonic (if possible on day `d`, also possible on day `d+1`), we can use binary search.

**Algorithm:**
1. **Early termination**: If `m * k > n`, return `-1` immediately.
2. **Binary search** on the range `[1, max(bloomDay)]`.
3. For each candidate day `mid`, check if it's possible to form `m` bouquets:
   - Traverse the array and count consecutive bloomed flowers (`bloomDay[i] <= mid`).
   - When consecutive count reaches `k`, increment bouquet count and reset consecutive counter.
   - Return `true` if bouquet count >= `m`.
4. If feasible at `mid`, search the left half (try smaller days). Otherwise, search the right half.

**Time Complexity:** O(n log(max(bloomDay)))
- Binary search: O(log(max(bloomDay))) iterations
- Each feasibility check: O(n)

**Space Complexity:** O(1)

```python
class Solution:
    def minDays(self, bloom: List[int], m: int, k: int) -> int:
        n = len(bloom)
        if m * k > n:
            return -1
        
        def check_possible(day: int) -> bool:
            # with `day` days, is it possible to have m consecutive flowers length k
            count = 0
            cur = 0
            for b in bloom:
                if day >= b:
                    cur += 1
                else:
                    cur = 0
                if cur >= k:
                    count += 1
                    cur = 0
            return count >= m
        
        left, right = 0, max(bloom)
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                right = mid - 1
            else:
                left = mid + 1
        
        return left
```

# Tags
#binary-search #greedy #array #medium

