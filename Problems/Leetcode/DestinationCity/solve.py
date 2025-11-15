from typing import List

class Solution:
    def destCity(self, paths: List[List[str]]) -> str:
        s = set()
        graph = {} # city -> adj cities
        for path in paths:
            a, b = path
            s.add(a)
            s.add(b)
            if a not in graph:
                graph[a] = []
            graph[a].append(b)
        
        for city in s:
            if city not in graph:
                return city
        return ""