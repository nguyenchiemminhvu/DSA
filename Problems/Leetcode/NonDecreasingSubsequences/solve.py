from typing import List

class Solution:
    def findSubsequences(self, nums: List[int]) -> List[List[int]]:
        res = set()
        tmp = []
        n = len(nums)
        def dfs(i: int) -> None:
            if len(tmp) > 1:
                res.add(tuple(tmp))
            
            if i >= n:
                return
            
            for j in range(i, n):
                if not tmp or tmp[-1] <= nums[j]:
                    tmp.append(nums[j])
                    dfs(j + 1)
                    tmp.pop()
        
        dfs(0)
        return [list(arr) for arr in res]