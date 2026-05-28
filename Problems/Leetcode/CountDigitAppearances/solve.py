from typing import List

class Solution:
    def countDigitOccurrences(self, nums: list[int], digit: int) -> int:
        # from functools import lru_cache
        # @lru_cache(None)
        # def count_d(val: int, d: int) -> int:
        #     c = 0
        #     while val:
        #         c += int((val % 10) == d)
        #         val //= 10
        #     return c
        # res = 0
        # for val in nums:
        #     res += count_d(val, digit)
        # return res

        return "".join(str(val) for val in nums).count(str(digit))