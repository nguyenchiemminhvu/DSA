from typing import List

class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res: List[str] = []
        temp: List[int] = []
        def dfs(open:int, close:int) -> bool:
            if open == n and close == n:
                # build string from temp
                s: str = "".join(['(' if val == 0 else ')' for val in temp])
                res.append(s)
                return True
            if open < n:
                temp.append(0)
                if dfs(open + 1, close):
                    pass
                temp.pop()
            if close < open:
                temp.append(1)
                if dfs(open, close + 1):
                    pass
                temp.pop()
            return False

        if dfs(0, 0):
            print('done')
        return res