class Solution:
    def maxUniqueSplit(self, s: str) -> int:
        count = [1]
        n = len(s)
        visited = set()
        def dfs(i: int) -> None:
            if i >= n:
                count[0] = max(count[0], len(visited))
                return
            for j in range(i, n):
                sub = s[i:j + 1]
                if sub not in visited:
                    visited.add(sub)
                    dfs(j + 1)
                    visited.remove(sub)
        dfs(0)
        return count[0]