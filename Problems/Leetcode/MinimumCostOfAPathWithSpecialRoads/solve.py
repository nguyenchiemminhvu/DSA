from collections import defaultdict
from typing import List
import heapq

class Solution:
    def minimumCost(self, start: List[int], target: List[int], roads: List[List[int]]) -> int:
        def dist(p1, p2):
            x1, y1 = p1
            x2, y2 = p2
            return abs(x2 - x1) + abs(y2 - y1)
        
        INF = 0xFFFFFFFF
        graph = defaultdict(lambda: defaultdict(lambda: int(INF)))
        
        points = set([tuple(start), tuple(target)])
        for x1, y1, x2, y2, _ in roads:
            points.add((x1, y1))
            points.add((x2, y2))
        
        for p1 in points:
            for p2 in points:
                if p1 == p2:
                    continue
                graph[p1][p2] = min(
                    graph[p1][p2],
                    dist(p1, p2)
                )
        
        for x1, y1, x2, y2, cost in roads:
            p1 = (x1, y1)
            p2 = (x2, y2)
            if dist(p1, p2) <= cost:
                continue
            graph[p1][p2] = min(
                graph[p1][p2],
                cost
            )
        
        n = len(points)
        shortest_dist = defaultdict(lambda: int(INF))
        shortest_dist[tuple(start)] = 0

        pq = [(0, tuple(start))]
        while pq:
            cur_dist, node = heapq.heappop(pq)
            if cur_dist > shortest_dist[node]:
                continue

            if node == target:
                return cur_dist
            
            for adj in graph[node]:
                next_cost = graph[node][adj]
                if cur_dist + next_cost < shortest_dist[adj]:
                    shortest_dist[adj] = cur_dist + next_cost
                    heapq.heappush(pq, (shortest_dist[adj], adj))
        
        return shortest_dist[tuple(target)]