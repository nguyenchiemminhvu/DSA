from typing import List

class Solution:
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        n = len(source)
        ng = len(cost)
        graph = [[float('inf')] * 26 for _ in range(26)]
        for i in range(26):
            graph[i][i] = 0
        for i in range(ng):
            sval = ord(original[i]) - ord('a')
            star = ord(changed[i]) - ord('a')
            graph[sval][star] = min(graph[sval][star], cost[i])

        # Floyd-Warshall algorithm
        for inter in range(26):
            for a in range(26):
                for b in range(26):
                    if graph[a][inter] != float('inf') and graph[inter][b] != float('inf'):
                        if graph[a][inter] + graph[inter][b] < graph[a][b]:
                            graph[a][b] = graph[a][inter] + graph[inter][b]

        total_cost = 0
        for i in range(n):
            if source[i] == target[i]:
                continue
            
            sval = ord(source[i]) - ord('a')
            star = ord(target[i]) - ord('a')
            dist = graph[sval][star]
            if dist == float('inf'):
                return -1
            total_cost += dist

        return total_cost