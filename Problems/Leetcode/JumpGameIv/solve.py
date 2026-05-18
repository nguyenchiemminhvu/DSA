from collections import defaultdict, deque
from typing import List

class Solution:
    def minJumps(self, arr: List[int]) -> int:
        n = len(arr)
        if n == 1:
            return 0
        
        val_idx = defaultdict(list)
        for i in range(n):
            val_idx[arr[i]].append(i)
        
        def bfs():
            q = deque([0])
            visited = set()
            visited.add(0)
            steps = 0
            while q:
                size = len(q)
                for _ in range(size):
                    cur = q.popleft()
                    if cur == n - 1:
                        return steps
                    
                    adj = []
                    if cur - 1 >= 0 and cur - 1 not in visited:
                        visited.add(cur - 1)
                        q.append(cur - 1)
                    if cur + 1 < n and cur + 1 not in visited:
                        visited.add(cur + 1)
                        q.append(cur + 1)
                    for idx in val_idx[arr[cur]]:
                        if idx not in visited:
                            visited.add(idx)
                            q.append(idx)
                    val_idx[arr[cur]].clear() # prevent looping the indexes on the same value
                steps += 1
            return -1
        
        return bfs()