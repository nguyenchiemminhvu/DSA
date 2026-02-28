class Solution:
    def concatenatedBinary(self, n: int) -> int:
        MOD = 10**9 + 7

        def count_bit(val:int) -> int:
            count = 0
            while val:
                val >>= 1
                count += 1
            return count

        # F(n) = (F(n - 1) << (num_bit_of_n) + n) % MOD
        def F(n: int) -> int:
            if n == 0:
                return 0
            
            val = ((F(n - 1) << count_bit(n)) + n) % MOD
            return val
        
        return F(n)