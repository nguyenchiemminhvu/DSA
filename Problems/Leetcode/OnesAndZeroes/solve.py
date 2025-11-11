from typing import List

class Solution:
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        counts = [(s.count('0'), s.count('1')) for s in strs]
        self.memo = {}

        def F(idx: int, m_left: int, n_left: int) -> int:
            if idx >= len(strs):
                return 0
            
            if (idx, m_left, n_left) in self.memo:
                return self.memo[(idx, m_left, n_left)]
            
            res = F(idx + 1, m_left, n_left)

            zeros, ones = counts[idx]
            if m_left >= zeros and n_left >= ones:
                res = max(res, 1 + F(idx + 1, m_left - zeros, n_left - ones))
            
            self.memo[(idx, m_left, n_left)] = res
            return res

        return F(0, m, n)