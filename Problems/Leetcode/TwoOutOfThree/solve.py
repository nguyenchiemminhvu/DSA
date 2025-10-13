from typing import List

class Solution:
    def twoOutOfThree(self, nums1: List[int], nums2: List[int], nums3: List[int]) -> List[int]:
        d = {}
        for val in nums1:
            d[val] = d.get(val, 0) | 0b1
        for val in nums2:
            d[val] = d.get(val, 0) | 0b10
        for val in nums3:
            d[val] = d.get(val, 0) | 0b100
        res = []
        for k, v in d.items():
            if v & (v - 1):
                res.append(k)
        return res