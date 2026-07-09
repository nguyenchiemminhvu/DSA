from collections import defaultdict, deque
from typing import List

class Solution:
    def validateBinaryTreeNodes(self, n: int, left: List[int], right: List[int]) -> bool:
        graph = defaultdict(list)
        parents = defaultdict(list)
        for i in range(n):
            if left[i] != -1:
                parents[left[i]].append(i)
                graph[i].append(left[i])
            if right[i] != -1:
                parents[right[i]].append(i)
                graph[i].append(right[i])
        
        root = -1
        for i in range(n):
            if i not in parents:
                if root == -1:
                    root = i
                else:
                    return False
            else:
                if len(parents[i]) > 1:
                    return False
                if i in parents[i]:
                    return False
        
        visited = set([root])
        q = deque([root])
        while q:
            cur = q.popleft()
            for adj in graph[cur]:
                if adj not in visited:
                    q.append(adj)
                    visited.add(adj)
        return len(visited) == n