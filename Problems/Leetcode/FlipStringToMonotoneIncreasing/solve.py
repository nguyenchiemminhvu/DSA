class Solution:
    def minFlipsMonoIncr(self, s: str) -> int:
        n = len(s)

        count_0 = 0
        suffix_0 = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            if s[i] == '0':
                count_0 += 1
            suffix_0[i] = count_0

        res = n
        count_1 = 0
        for i, c in enumerate(s):
            if c == '1':
                # keep this one as 1
                res = min(res, count_1 + suffix_0[i + 1])
                count_1 += 1
                # turn it to 0
                res = min(res, count_1 + suffix_0[i + 1])
            else:
                # keep this one as 0
                res = min(res, count_1 + suffix_0[i + 1])
                # turn it to 1
                res = min(res, count_1 + suffix_0[i])
        return res