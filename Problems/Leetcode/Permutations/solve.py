from typing import List

class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        n = len(nums)
        s = set()
        temp = []
        res = []
        def dfs(i:int) -> None:
            if i == n:
                res.append([val for val in temp])
                return
            for val in nums:
                if val not in s:
                    temp.append(val)
                    s.add(val)
                    dfs(i + 1)
                    s.remove(val)
                    temp.pop()

        dfs(0)
        return res