from typing import List

class Solution:
    def maxLength(self, arr: List[str]) -> int:
        n = len(arr)
        res = [0]
        ss = set()
        tmp = []
        def dfs(i: int) -> None:
            res[0] = max(res[0], sum(len(arr[idx]) for idx in tmp))
            for j in range(i, n):
                word = arr[j]
                if len(set(word)) != len(word):
                    continue
                if any(c in ss for c in word):
                    continue
                for c in word:
                    ss.add(c)
                tmp.append(j)
                dfs(j + 1)
                tmp.pop()
                for c in word:
                    ss.remove(c)
        dfs(0)
        return res[0]