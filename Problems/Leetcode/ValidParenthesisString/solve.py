class Solution:
    def checkValidString(self, s: str) -> bool:
        n = len(s)
        memo = {}

        def dfs(i:int, count_open:int) -> bool:
            if count_open < 0:
                return False
            if i == n:
                return (count_open == 0)

            if (i, count_open) in memo:
                return memo[(i, count_open)]

            res = True
            if s[i] == '(':
                res = dfs(i + 1, count_open + 1)
            elif s[i] == ')':
                res = dfs(i + 1, count_open - 1)
            else:
                # asterisk
                res =   dfs(i + 1, count_open) or \
                        dfs(i + 1, count_open + 1) or \
                        dfs(i + 1, count_open - 1)
            memo[(i, count_open)] = res
            return res

        return dfs(0, 0)