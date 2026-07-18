from collections import defaultdict, deque
from typing import List

class Solution:
    def findAllRecipes(self, recipes: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        n = len(recipes)
        graph = defaultdict(list)
        in_degree = defaultdict(int)
        for i in range(n):
            for ingredient in ingredients[i]:
                graph[ingredient].append(recipes[i])
                in_degree[recipes[i]] += 1
        
        s = set()
        q = deque(supplies)
        while q:
            supply = q.popleft()
            for ingredient in graph[supply]:
                in_degree[ingredient] -= 1
                if in_degree[ingredient] == 0:
                    q.append(ingredient)
                    s.add(ingredient)
        return list(s)