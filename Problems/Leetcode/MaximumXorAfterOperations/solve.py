from typing import List

class Solution:
    def maximumXOR(self, nums: List[int]) -> int:
        # s = set()
        # for val in nums:
        #     i = 0
        #     while val:
        #         if val & 1:
        #             s.add(i)
        #         i += 1
        #         val >>= 1
        # res = 0
        # for i in range(28):
        #     if i in s:
        #         res |= (1 << i)
        # return res

        res = 0
        for val in nums:
            res |= val
        return res