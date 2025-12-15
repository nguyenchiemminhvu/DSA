class Solution:
    def countArrangement(self, n: int) -> int:
        count = 0
        used = set()
        def dfs(i: int) -> None:
            nonlocal count
            if i >= n:
                count += 1
                return
            
            for val in range(1, n+1):
                if (i + 1) % val == 0 or val % (i + 1) == 0:
                    if val not in used:
                        used.add(val)
                        dfs(i + 1)
                        used.remove(val)
        
        dfs(0)
        return count