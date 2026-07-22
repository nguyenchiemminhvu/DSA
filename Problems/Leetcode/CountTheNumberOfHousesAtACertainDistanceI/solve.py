from collections import defaultdict, deque
from typing import List

class Solution:
    def countOfPairs(self, n: int, x: int, y: int) -> List[int]:
        k_count = defaultdict(int)
        graph = defaultdict(list)
        for i in range(2, n + 1):
            graph[i].append(i - 1)
            graph[i - 1].append(i)
        
        if abs(x - y) != 1:
            graph[x].append(y)
            graph[y].append(x)

        def bfs(start: int):
            INF = 0x7FFFFFFF
            q = deque([start])
            visited = set([start])
            steps = -1
            while q:
                steps += 1
                count = len(q)
                for _ in range(count):
                    cur = q.popleft()
                    k_count[steps] += 1
                    for adj in graph[cur]:
                        if adj not in visited:
                            visited.add(adj)
                            q.append(adj)
            
        
        for i in range(1, n + 1):
            bfs(i)
        
        return [k_count[i] for i in range(1, n + 1)]