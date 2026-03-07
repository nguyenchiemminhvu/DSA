class Solution:
    def minFlips(self, s: str) -> int:
        n = len(s)
        s += s
        new_n = len(s)

        pattern1 = ''
        pattern2 = ''
        for i in range(new_n):
            pattern1 += '1' if i & 1 else '0'
            pattern2 += '0' if i & 1 else '1'

        diff1 = 0
        diff2 = 0
        for i in range(n):
            if s[i] != pattern1[i]:
                diff1 += 1
            if s[i] != pattern2[i]:
                diff2 += 1
        
        res = min(diff1, diff2)
        left = 0
        for right in range(n, new_n):
            if s[right] != pattern1[right]:
                diff1 += 1
            if s[right] != pattern2[right]:
                diff2 += 1
            
            if s[left] != pattern1[left]:
                diff1 -= 1
            if s[left] != pattern2[left]:
                diff2 -= 1
            left += 1
            
            res = min(res, min(diff1, diff2))
        return res