class Solution:
    def minOperations(self, n: int) -> int:
        res = 0
        i = n // 2
        op = 0
        if n % 2 == 0:
            i -= 1
            op += 1
        
        for j in range(i, -1, -1):
            res += op
            op += 2
        return res