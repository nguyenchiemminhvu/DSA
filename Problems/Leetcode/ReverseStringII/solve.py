class Solution:
    def reverseStr(self, s: str, k: int) -> str:
        s = list(s)
        n = len(s)
        r = False
        for i in range(0, n, k):
            r = not r
            if not r:
                continue
            left = i
            right = min(i + k - 1, n - 1)
            while left <= right:
                s[left], s[right] = s[right], s[left]
                left += 1
                right -= 1
        return "".join(s)