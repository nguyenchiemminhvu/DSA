class Solution:
    def kLengthApart(self, nums: List[int], k: int) -> bool:
        n = len(nums)
        c0 = 0xFFFFFFFF
        for val in nums:
            if val == 0:
                c0 += 1
            else:
                if c0 < k:
                    return False
                c0 = 0
        return True