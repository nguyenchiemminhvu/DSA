from typing import List

class Solution:
    def maxDistance(self, nums1: List[int], nums2: List[int]) -> int:
        res = 0
        n1 = len(nums1)
        n2 = len(nums2)
        i1 = n1 - 1
        i2 = n2 - 1
        while i1 >= 0 and i2 >= 0:
            if nums1[i1] <= nums2[i2]:
                res = max(res, i2 - i1)
                i1 -= 1
            else:
                i2 -= 1
        return res