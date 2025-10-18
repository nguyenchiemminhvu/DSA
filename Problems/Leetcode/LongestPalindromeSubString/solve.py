class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        memo = set()
        for i in range(n):
            memo.add((i, i))
            if i > 0 and s[i] == s[i - 1]:
                memo.add((i-1, i))

        for cur_len in range(2, n):
            for i in range(cur_len, n):
                l = i - cur_len
                r = i
                if (l + 1, r - 1) in memo and s[l] == s[r]:
                    memo.add((l, r))
        
        res = ""
        for p in memo:
            if len(res) < (p[1] - p[0] + 1):
                res = s[p[0]:p[1] + 1]
        return res