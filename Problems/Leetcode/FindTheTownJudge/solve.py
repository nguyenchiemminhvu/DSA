from typing import List

class Solution:
    def findJudge(self, n: int, trust: List[List[int]]) -> int:
        if n == 1:
            return 1
        count_in = [0] * (n + 1)
        count_out = [0] * (n + 1)
        for a, b in trust:
            count_in[b] += 1
            count_out[a] += 1
        
        for i, count in enumerate(count_in):
            if count == n - 1:
                if count_out[i] == 0:
                    return i
        return -1