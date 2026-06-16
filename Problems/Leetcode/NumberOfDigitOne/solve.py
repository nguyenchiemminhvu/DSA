class Solution:
    def countDigitOne(self, n: int) -> int:
        s = str(n)
        n = len(s)

        from functools import lru_cache
        @lru_cache(None)
        def F(i: int, count: int, is_tight: bool) -> int:
            if i >= n:
                return count
            
            limit = int(s[i]) if is_tight else 9
            total = 0
            for digit in range(limit + 1):
                next_tight = is_tight and digit == limit
                next_count = count + (1 if digit == 1 else 0)
                total += F(i + 1, next_count, next_tight)
            return total
        
        return F(0, 0, True)