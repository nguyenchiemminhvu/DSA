from typing import List

class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        s = set()
        n = len(nums)
        tmp = []
        visited = [False] * n
        def generating(idx: int) -> None:
            if idx >= n:
                s.add(tuple(tmp))
                return
            
            for i in range(n):
                if not visited[i]:
                    visited[i] = True
                    tmp.append(nums[i])
                    generating(idx + 1)
                    tmp.pop()
                    visited[i] = False
        
        generating(0)
        return [list(arr) for arr in s]