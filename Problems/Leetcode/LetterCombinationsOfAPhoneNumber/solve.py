from typing import List

class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        text = ["", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
        n = len(digits)
        res = []
        temp = []
        def dfs(i: int) -> None:
            if i == n:
                if len(temp) > 0:
                    res.append("".join(temp))
                return
            button_id = ord(digits[i]) - ord('0')
            for c in text[button_id]:
                temp.append(c)
                dfs(i + 1)
                temp.pop()

        dfs(0)
        return res