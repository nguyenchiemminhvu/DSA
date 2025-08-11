# https://leetcode.com/problems/range-product-queries-of-powers

from typing import List

MOD = 1000000007
class Solution:
    def productQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        powers = []
        i = 0
        while (n):
            if (n & 1):
                powers.append(1 << i)
            i += 1
            n >>= 1
        
        res = []
        for query in queries:
            val = 1
            for i in range(query[0], query[1] + 1):
                val = ((val % MOD) * (powers[i] % MOD)) % MOD
            res.append(val)
        return res

if __name__ == "__main__":
    sol = Solution()
    n = 5
    queries = [[0, 0], [0, 1], [1, 2]]
    print(sol.productQueries(n, queries))  # Output: [1, 6, 4]