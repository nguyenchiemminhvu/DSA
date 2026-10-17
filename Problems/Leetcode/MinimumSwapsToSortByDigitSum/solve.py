from typing import List

class Solution:
    def minSwaps(self, nums: List[int]) -> int:
        n = len(nums)

        def sum_digits(val: int):
            s = 0
            while val:
                s += (val % 10)
                val //= 10
            return s

        pairs = [[sum_digits(val), val, i] for i, val in enumerate(nums)]
        pairs.sort()

        res = 0
        visited = {i: False for i in range(n)}
        for i in range(n):
            if pairs[i][2] == i:
                continue
            
            cycle_size = 0
            j = i
            while not visited[j]:
                visited[j] = True
                j = pairs[j][2]
                cycle_size += 1
            
            if cycle_size > 0:
                res += cycle_size - 1
        
        return res