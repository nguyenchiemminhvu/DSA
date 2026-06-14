from typing import List

class Solution:
    def candy(self, rate: List[int]) -> int:
        n = len(rate)
        temp = [1] * n
        for i in range(1, n):
            if rate[i] > rate[i - 1]:
                temp[i] = temp[i - 1] + 1
        
        for i in range(n - 2, -1, -1):
            if rate[i] > rate[i + 1]:
                temp[i] = max(temp[i], temp[i + 1] + 1)
        
        return sum(temp)