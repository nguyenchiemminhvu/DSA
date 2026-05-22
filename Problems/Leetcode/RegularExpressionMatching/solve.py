class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        ns = len(s)
        np = len(p)

        mem = {}
        def F(idx_s: int, idx_p: int) -> bool:
            if idx_s < 0:
                if idx_p < 0:
                    return True
                if idx_p >= 1 and p[idx_p] == '*':
                    return F(idx_s, idx_p - 2)
                return False
            if idx_p < 0:
                return idx_s < 0
            
            if (idx_s, idx_p) in mem:
                return mem[(idx_s, idx_p)]

            res = False
            if p[idx_p] == '*':
                target_ch = p[idx_p - 1]
                res = res or F(idx_s, idx_p - 2)
                if s[idx_s] == target_ch or target_ch == '.':
                    res = res or F(idx_s - 1, idx_p)
            elif p[idx_p] == '.' or s[idx_s] == p[idx_p]:
                res = res or F(idx_s - 1, idx_p - 1)
            else:
                res = False
            
            mem[(idx_s, idx_p)] = res
            return res
        
        return F(ns - 1, np - 1)