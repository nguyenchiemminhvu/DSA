class Solution:
    def smallestNumber(self, n: int, t: int) -> int:
        def product(val: int) -> int:
            p = 1
            while val:
                p *= (val % 10)
                val //= 10
            return p
        
        for i in range(100):
            val = product(n + i)
            if val % t == 0:
                return n + i
        return -1