from typing import List
import heapq

class Solution:
    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        n = len(points)

        # res = 0
        # visited = set([0])
        # while len(visited) < n:
        #     unvisited = set([i for i in range(n)]) - visited
        #     min_dist = float('inf')
        #     chosen = float('inf')
        #     for u in unvisited:
        #         for v in visited:
        #             dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1])
        #             if min_dist > dist:
        #                 min_dist = dist
        #                 chosen = u
        #     visited.add(chosen)
        #     res += min_dist
        # return res

        class DSU:
            def __init__(self, size: int):
                self.parent = list(range(size))
                self.rank = [0] * size

            def find(self, i: int) -> int:
                if self.parent[i] == i:
                    return i
                self.parent[i] = self.find(self.parent[i])
                return self.parent[i]

            def union(self, i: int, j: int) -> bool:
                root_i = self.find(i)
                root_j = self.find(j)
                
                if root_i == root_j:
                    return False

                if self.rank[root_i] < self.rank[root_j]:
                    self.parent[root_i] = root_j
                elif self.rank[root_i] > self.rank[root_j]:
                    self.parent[root_j] = root_i
                else:
                    self.parent[root_j] = root_i
                    self.rank[root_i] += 1
                return True
        
        dsu = DSU(n)
        edges = []
        for i in range(n):
            for j in range(i + 1, n):
                dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])
                heapq.heappush(edges, (dist, i, j))
        
        count = 0
        total_cost = 0
        while edges:
            d, i, j = heapq.heappop(edges)
            if dsu.union(i, j):
                count += 1
                total_cost += d
                if count == n - 1:
                    break
        return total_cost