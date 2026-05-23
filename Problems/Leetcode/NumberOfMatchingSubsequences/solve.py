from typing import List

class Solution:
    def numMatchingSubseq(self, s: str, words: List[str]) -> int:
        n = len(s)

        # res = 0
        # for word in words:
        #     nw = len(word)
        #     i = 0
        #     iw = 0
        #     while i < n and iw < nw:
        #         if s[i] == word[iw]:
        #             iw += 1
        #         i += 1
        #     if iw == nw:
        #         res += 1
        # return res

        # dp[i][c] -> next index of c appears in s start from i
        dp = [[n] * 26 for _ in range(n + 1)]

        # last_idx = {}
        # for i in range(n - 1, -1, -1):
        #     last_idx[ord(s[i]) - ord('a')] = i
        #     for c, idx in last_idx.items():
        #         dp[i][c] = idx

        for i in range(n - 1, -1, -1):
            dp[i] = dp[i + 1][:]
            dp[i][ord(s[i]) - ord('a')] = i
        
        res = 0
        for word in words:
            nw = len(word)
            i = 0
            iw = 0
            while i < n and iw < nw:
                found = dp[i][ord(word[iw]) - ord('a')]
                if found < n:
                    iw += 1
                i = found + 1
            if iw == nw:
                res += 1
        return res