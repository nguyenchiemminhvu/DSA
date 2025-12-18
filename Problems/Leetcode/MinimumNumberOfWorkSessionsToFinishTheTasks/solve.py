from typing import List

class Solution:
    def minSessions(self, tasks: List[int], limit: int) -> int:
        n = len(tasks)
        tasks.sort(reverse=True)
        res = [n]
        used = set()
        tmp = []
        def dfs(i: int) -> None:
            if len(tmp) >= res[0]:
                return
            if i >= n:
                res[0] = min(res[0], len(tmp))
                return
            
            # try adding task i to any current session without passing limit time
            for j in range(len(tmp)):
                if i not in used:
                    if tmp[j] + tasks[i] <= limit:
                        tmp[j] += tasks[i]
                        used.add(i)
                        dfs(i + 1)
                        used.remove(i)
                        tmp[j] -= tasks[i]
            
            # make task i a new session
            if i not in used:
                tmp.append(tasks[i])
                used.add(i)
                dfs(i + 1)
                used.remove(i)
                tmp.pop()
        
        dfs(0)
        return res[0]