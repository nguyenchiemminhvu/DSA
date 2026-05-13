from typing import List, Tuple

class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        n = len(nums)

        # global_max = [nums[0]]
        # mem = {}
        # def F(i: int) -> Tuple[int]:
        #     if i == 0:
        #         return (nums[0], nums[0])
        #     if i in mem:
        #         return mem[i]
        #     mi, ma = F(i - 1)
        #     local_min = min(nums[i], nums[i] * mi, nums[i] * ma)
        #     local_max = max(nums[i], nums[i] * mi, nums[i] * ma)
        #     global_max[0] = max(global_max[0], local_max)
        #     mem[i] = (local_min, local_max)
        #     return (local_min, local_max)
        # F(n - 1)
        # return global_max[0]

        res = nums[0]
        cur_min = cur_max = nums[0]
        for i in range(1, n):
            val = nums[i]
            tmp_min = min(val, val * cur_min, val * cur_max)
            tmp_max = max(val, val * cur_min, val * cur_max)
            cur_min, cur_max = tmp_min, tmp_max
            res = max(res, tmp_max)
        return res