from typing import List

class Solution:
    def kConcatenationMaxSum(self, arr: List[int], k: int) -> int:
        mod = 10**9 + 7

        def kadane(cur_max, max_all):
            for val in arr:
                cur_max = max(val, cur_max + val)
                max_all = max(max_all, cur_max)
            return cur_max, max_all

        total = sum(arr)

        first_cur_max, first_max_all = kadane(0, 0)
        
        if k == 1:
            return first_max_all % mod
        
        second_cur_max, second_max_all = kadane(first_cur_max, first_max_all)

        if total <= 0:
            return second_max_all % mod
        
        return (second_max_all + (k - 2) * total) % mod