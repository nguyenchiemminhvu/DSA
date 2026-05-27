class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)

        def parse_len(l: int) -> int:
            if l <= 0:
                return 0
            if l == 1:
                return 1
            if l < 10:
                return 2
            if l < 100:
                return 3
            return 4
        
        mem = {}
        def F(i: int, cnt: int) -> int:
            if cnt < 0:
                return float('inf')
            if i >= n or n - i <= cnt:
                return 0
            if (i, cnt) in mem:
                return mem[(i, cnt)]
            
            # delete a character
            res = F(i + 1, cnt - 1)
            
            # keep s[i], build run-length
            same = 0
            delete = 0
            for j in range(i, n):
                if s[j] == s[i]:
                    same += 1
                    res = min(res, parse_len(same) + F(j + 1, cnt - delete))
                else:
                    delete += 1
                    if delete > cnt:
                        break
            
            mem[(i, cnt)] = res
            return res
        
        return F(0, k)