from typing import List

class Solution:
    def pyramidTransition(self, bottom: str, allowed: List[str]) -> bool:
        check = {}
        memo = {}

        for s in allowed:
            left, right, up = s[0], s[1], s[2]
            if (left, right) not in check:
                check[(left, right)] = []
            check[(left, right)].append(up)
        
        def build_upper_row(row: str) -> List[str]:
            res = []
            n = len(row)
            def backtrack(i: int, tmp: List[str]) -> None:
                if i == n - 1:
                    res.append("".join(tmp))
                    return

                pair = (row[i], row[i + 1])
                if pair not in check:
                    return

                for ch in check[pair]:
                    tmp.append(ch)
                    backtrack(i + 1, tmp)
                    tmp.pop()
            backtrack(0, [])
            return res
        
        def dfs(row: str) -> bool:
            if len(row) == 1:
                return True
            
            if row in memo:
                return memo[row]
            
            upper = build_upper_row(row)
            for up in upper:
                if dfs(up):
                    return True
            
            memo[row] = False
            return False

        return dfs(bottom)