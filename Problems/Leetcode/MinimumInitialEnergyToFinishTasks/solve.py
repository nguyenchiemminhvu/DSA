from typing import List

class Solution:
    def minimumEffort(self, tasks: List[List[int]]) -> int:
        tasks.sort(key=lambda x: x[1] - x[0], reverse=True)
        
        res = 0
        cur = 0
        for actual, minimum in tasks:
            if cur < minimum:
                res += minimum - cur
                cur = minimum
            cur -= actual
        return res