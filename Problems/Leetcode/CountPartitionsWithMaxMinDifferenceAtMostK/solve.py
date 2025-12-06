from typing import List

class Solution:
    def countPartitions(self, nums: List[int], k: int) -> int:
        n = len(nums)
        mod = 10**9 + 7
        memo = {}
        # number of valid ways to partition nums[i:]
        #(starting a new segment beginning at index i)
        def F(i: int) -> int:
            # Base case: reached end → 1 valid partition
            if i == n:
                return 1
            
            if i in memo:
                return memo[i]

            ways = 0
            cur_min = float('inf')
            cur_max = float('-inf')

            # Try extending segment [i..j]
            for j in range(i, n):
                cur_min = min(cur_min, nums[j])
                cur_max = max(cur_max, nums[j])

                if cur_max - cur_min > k:
                    break

                ways += F(j + 1)

            memo[i] = ways % mod
            return ways % mod

        return F(0)