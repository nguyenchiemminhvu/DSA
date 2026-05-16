class Solution:
    def countSubstrings(self, s: str) -> int:
        n = len(s)

        # mem = {}
        # def F(l: int, r: int) -> int:
        #     if l < 0 or r >= n:
        #         return 0
        #     if (l, r) in mem:
        #         return mem[(l, r)]
        #     ways = 0
        #     if s[l] == s[r]:
        #         ways = 1 + F(l - 1, r + 1)
        #     mem[(l, r)] = ways
        #     return ways
        # res = 0
        # for i in range(n):
        #     res += F(i, i)
        #     res += F(i, i + 1)
        # return res

        res = 0
        def count_palin(l: int, r: int) -> int:
            count = 0
            while l >= 0 and r < n and s[l] == s[r]:
                count += 1
                l -= 1
                r += 1
            return count
        
        for i in range(n):
            res += count_palin(i, i)
            if i + 1 < n:
                res += count_palin(i, i + 1)
        return res