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
        count = 0  # number of colors currently in the "top group"

        while need > 0 and i < n:
            cur_val = nums[i]

            j = i
            while j < n and nums[j] == cur_val:
                j += 1

            # colors in play are indices [0..j-1]
            count = j

            next_val = nums[j] if j < n else 0
            diff = cur_val - next_val
            can_sell = diff * count

            if can_sell <= need:
                # sell all levels: cur_val, cur_val-1, ..., next_val+1 for each of count colors
                res += count * arith_sum(cur_val, next_val + 1)
                res %= MOD
                need -= can_sell
                i = j
            else:
                # only sell part of these levels
                full, rem = divmod(need, count)
                low_after_full = cur_val - full

                res += count * arith_sum(cur_val, low_after_full + 1)
                res %= MOD

                res += rem * low_after_full
                res %= MOD
                return res % MOD

        return res % MOD