class Solution:
    def longestPalindromicSubsequence(self, s: str, k: int) -> int:
        s = [ord(c) - ord('a') for c in s]
        n = len(s)

        def min_dist(a: int, b: int) -> int:
            d = abs(a - b)
            return min(d, 26 - d)
        def prev_ch(c: int, step: int = 1) -> int:
            return ((c - step) + 26) % 26
        def next_ch(c: int, step: int = 1) -> int:
            return (c + step) % 26
        
        # mem = {}
        # def F(l: int, r: int, cnt: int) -> int:
        #     if l > r:
        #         return 0
        #     if l == r:
        #         return 1
        #     if (l, r, cnt) in mem:
        #         return mem[(l, r, cnt)]
        #     res = 0
        #     if s[l] == s[r]:
        #         res = max(res, 2 + F(l + 1, r - 1, cnt))
        #     else:
        #         res = max(res, F(l + 1, r, cnt), F(l, r - 1, cnt))
        #         # try replacement
        #         dist = min_dist(s[l], s[r])
        #         if cnt + dist <= k:
        #             prev_l = prev_ch(s[l], dist)
        #             if prev_l == s[r]:
        #                 res = max(res, 2 + F(l + 1, r - 1, cnt + dist))
        #             next_l = next_ch(s[l], dist)
        #             if next_l == s[r]:
        #                 res = max(res, 2 + F(l + 1, r - 1, cnt + dist))
        #     mem[(l, r, cnt)] = res
        #     return res
        # return F(0, n - 1, 0)

        dp = [[[0] * (k + 1) for _ in range(n)] for _ in range(n)]
        for i in range(n):
            for cnt in range(k + 1):
                dp[i][i][cnt] = 1
        
        for l in range(n - 1, -1, -1):
            for r in range(l + 1, n):
                for cnt in range(k, -1, -1):
                    if s[l] == s[r]:
                        dp[l][r][cnt] = max(dp[l][r][cnt], 2 + dp[l + 1][r - 1][cnt])
                    else:
                        dp[l][r][cnt] = max(dp[l][r][cnt], dp[l + 1][r][cnt], dp[l][r - 1][cnt])

                        # try replacement
                        dist = min_dist(s[l], s[r])
                        if cnt + dist <= k:
                            prev_l = prev_ch(s[l], dist)
                            if prev_l == s[r]:
                                dp[l][r][cnt] = max(dp[l][r][cnt], 2 + dp[l + 1][r - 1][cnt + dist])
                            next_l = next_ch(s[l], dist)
                            if next_l == s[r]:
                                dp[l][r][cnt] = max(dp[l][r][cnt], 2 + dp[l + 1][r - 1][cnt + dist])

        return dp[0][n - 1][0]