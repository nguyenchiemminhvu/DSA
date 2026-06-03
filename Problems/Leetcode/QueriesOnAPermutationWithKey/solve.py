from typing import List

class Solution:
    def processQueries(self, queries: List[int], m: int) -> List[int]:
        p = [i for i in range(1, m + 1)]
        res = []
        for query in queries:
            idx = p.index(query)
            p = [query] + p[:idx] + p[idx + 1:]
            res.append(idx)
        return res