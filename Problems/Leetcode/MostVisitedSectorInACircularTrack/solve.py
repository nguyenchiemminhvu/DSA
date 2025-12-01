from typing import List

class Solution:
    def mostVisited(self, n: int, rounds: List[int]) -> List[int]:
        prefix = [0] * (n + 2)

        cur = rounds[0]
        for i in range(len(rounds)):
            target = rounds[i]
            if cur <= target:
                prefix[cur] += 1
                prefix[target + 1] -= 1
            else:
                prefix[1] += 1
                prefix[target + 1] -= 1
                prefix[cur] += 1
                prefix[n + 1] -= 1
            cur = target + 1
        for i in range(1, len(prefix)):
            prefix[i] += prefix[i - 1]
        
        res = []
        max_visited = max(prefix)
        for i in range(1, n + 1):
            if prefix[i] == max_visited:
                res.append(i)
        return res