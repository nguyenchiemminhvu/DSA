class Solution:
    def orderlyQueue(self, s: str, k: int) -> str:
        if k > 1:
            return ''.join(sorted(list(s)))
        
        min_s = s
        n = len(s)
        for i in range(n):
            # try n times rotation
            s = s[1:] + s[0]
            min_s = min(min_s, s)
        return min_s