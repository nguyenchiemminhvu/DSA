class Solution:
    def countRotations(self, s: str, k: int) -> int:
        n = len(s)

        count = 0
        for i in range(1, n):
            if s[i] == s[i - 1]:
                count += 1
        
        res = int(count == k)
        for _ in range(n - 1):
            if s[1] == s[0]:
                count -= 1
            
            s = s[1:] + s[0]
            
            if s[-1] == s[-2]:
                count += 1
            
            res += int(count == k)
        
        return res