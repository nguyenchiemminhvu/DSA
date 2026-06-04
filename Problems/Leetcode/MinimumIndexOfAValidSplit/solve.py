from collections import Counter
from typing import List

class Solution:
    def minimumIndex(self, nums: List[int]) -> int:
        n = len(nums)
        counter = Counter(nums)
        max_count = 0
        dval = -1

        for k, v in counter.items():
            if max_count < v:
                max_count = v
                dval = k
        
        count_dval = 0
        for i in range(n - 1):
            if nums[i] == dval:
                count_dval += 1

            nleft = i + 1
            nright = n - nleft
            count_dval_right = max_count - count_dval
            if count_dval > (nleft // 2) and count_dval_right > (nright // 2):
                return i

        return -1