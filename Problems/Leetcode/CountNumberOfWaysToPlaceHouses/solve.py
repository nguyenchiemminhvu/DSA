class Solution:
    def countHousePlacements(self, n: int) -> int:
        mod = 10**9 + 7
        dp = [0] * (n + 1)
        dp[0] = 1
        dp[1] = 1
        for i in range(1, n + 1):
            dp[i] += dp[i - 1]
            if i - 2 >= 0:
                dp[i] += dp[i - 2]
            dp[i] %= mod
        return ((dp[n] % mod) * (dp[n] % mod)) % mod