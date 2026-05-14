class Solution:
    def countGoodStrings(self, low: int, high: int, zero: int, one: int) -> int:
        mod = 10**9 + 7
        coins = [zero, one]

        # mem = {}
        # def F(amount: int) -> int:
        #     nonlocal mod
        #     if amount < 0:
        #         return 0
        #     if amount == 0:
        #         return 1
        #     if amount in mem:
        #         return mem[amount]
        #     ways = 0
        #     for i in range(len(coins)):
        #         ways = ((ways % mod) + (F(amount - coins[i]) % mod)) % mod
        #     mem[amount] = ways
        #     return ways
        # res = 0
        # for i in range(low, high + 1):
        #     res = ((res % mod) + (F(i) % mod)) % mod
        # return res

        dp = [0 for _ in range(high + 1)]
        dp[0] = 1
        res = 0
        for amount in range(high + 1):
            for i in range(len(coins)):
                if coins[i] <= amount:
                    dp[amount] = ((dp[amount] % mod) + (dp[amount - coins[i]] % mod)) % mod
            if amount >= low and amount <= high:
                res = ((res % mod) + (dp[amount] % mod)) % mod
        return res