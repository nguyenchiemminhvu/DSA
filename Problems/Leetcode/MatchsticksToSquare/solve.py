from typing import List

class Solution:
    def makesquare(self, nums: List[int]) -> bool:
        s = sum(nums)
        k = 4
        if s % k != 0:
            return False
        
        n = len(nums)
        target = s // k
        nums.sort(reverse=True)
        if nums[0] > target:
            return False
        used = [False] * n
        def dfs(i: int, cur_sum: int, segments:int) -> bool:
            if segments == 1:
                return True
            if cur_sum == target:
                return dfs(0, 0, segments - 1)
            for j in range(i, n):
                if used[j] or cur_sum + nums[j] > target:
                    continue
                used[j] = True
                if dfs(j + 1, cur_sum + nums[j], segments):
                    return True
                used[j] = False
            return False
        
        return dfs(0, 0, k)