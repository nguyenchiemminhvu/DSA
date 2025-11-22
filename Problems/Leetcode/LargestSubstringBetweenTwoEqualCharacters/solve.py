class Solution:
    def maxLengthBetweenEqualCharacters(self, s: str) -> int:
        prefix = [[-1, -1] for _ in range(26)]
        for i, c in enumerate(s):
            ip = ord(c) - ord('a')
            if prefix[ip][0] == -1:
                prefix[ip][0] = i
            else:
                prefix[ip][1] = i
        
        res = -1
        for i in range(26):
            left, right = prefix[i]
            if right > left:
                res = max(res, right - left - 1)
        return res