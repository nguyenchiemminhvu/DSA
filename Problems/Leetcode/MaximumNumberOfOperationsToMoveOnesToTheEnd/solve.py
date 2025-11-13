class Solution:
    def maxOperations(self, s: str) -> int:
        count_1, count_0, res = [0, 0, 0]
        s += '1'
        n = len(s)
        for i in range(n):
            if s[i] == '1':
                if count_0 > 0:
                    count_0 = 0
                    res += count_1
                count_1 += 1
            else:
                count_0 += 1
        return res