class Solution:
    def maxRepeating(self, s: str, word: str) -> int:
        ns = len(s)
        nw = len(word)
        left = 1
        right = ns // nw
        res = 0
        while left <= right:
            mid = left + (right - left) // 2
            if s.find(word * mid) != -1:
                res = mid
                left = mid + 1
            else:
                right = mid - 1
        return res