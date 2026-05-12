from typing import List

class Solution:
    def minMutation(self, start: str, end: str, bank: List[str]) -> int:
        if start == end:
            return 0
        if end not in bank:
            return -1
        if not bank:
            return -1
        
        def count_diff(a: str, b: str) -> int:
            diff = 0
            for i in range(len(a)):
                diff += 1 if a[i] != b[i] else 0
            return diff

        arr = list(set([start, end] + bank))
        start_idx = arr.index(start)
        end_idx = arr.index(end)
        
        n = len(arr)
        graph = [[float('inf') for _ in range(n)] for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if i == j:
                    graph[i][j] = 0
                else:
                    diff = count_diff(arr[i], arr[j])
                    if diff == 0:
                        graph[i][j] = 0
                    elif diff == 1:
                        graph[i][j] = 1
        
        # floyed warshall algorithm
        for mid in range(n):
            for i in range(n):
                for j in range(n):
                    if graph[i][mid] != float('inf') and graph[mid][j] != float('inf'):
                        graph[i][j] = min(graph[i][j], graph[i][mid] + graph[mid][j])

        return -1 if graph[start_idx][end_idx] == float('inf') else graph[start_idx][end_idx]