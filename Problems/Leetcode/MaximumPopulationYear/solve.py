from typing import List

class Solution:
    def maximumPopulation(self, logs: List[List[int]]) -> int:
        prefix = [0] * (2055 - 1950)
        for log in logs:
            b, d = log
            prefix[b - 1950] += 1
            prefix[d - 1950] -= 1
        for i in range(1, len(prefix)):
            prefix[i] += prefix[i - 1]
        
        max_population = max(prefix)
        for i in range(len(prefix)):
            if prefix[i] == max_population:
                return i + 1950
        return 0