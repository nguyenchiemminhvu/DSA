class Solution:
    def findTheLongestBalancedSubstring(self, s: str) -> int:
        res = 0
        count_0 = 0
        count_1 = 0
        prev = '#'
        for c in s:
            if c == '0':
                count_1 = 0
                if prev == '1':
                    count_0 = 1
                else:
                    count_0 += 1
            else:
                count_1 += 1
            prev = c
            res = max(res, min(count_0, count_1) * 2)
        return res