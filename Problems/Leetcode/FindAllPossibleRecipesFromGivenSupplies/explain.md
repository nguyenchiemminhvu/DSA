## Problem

https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/

Given `n` recipes, their ingredient lists, and an initial set of supplies (available in infinite quantity), return all recipes you can create. A recipe can itself be used as an ingredient for another recipe.

---

## Observations

1. **Dependency graph**: A recipe depends on its ingredients. If we model this as a directed graph where an edge `A → B` means "A is needed to make B", the problem becomes: starting from known supplies, which recipes become reachable?

2. **Topological ordering (Kahn's algorithm)**: A recipe can be made when all its ingredients are available. This maps directly to the concept of **in-degree** in a dependency graph — a recipe with in-degree 0 (all ingredients satisfied) can be produced.

3. **Recipes can depend on other recipes**: This creates a chain. Making one recipe may unlock another. Kahn's BFS handles this naturally — when a recipe is produced, it acts like a new supply, potentially reducing the in-degree of other recipes.

4. **Cycles are implicitly handled**: If two recipes require each other and neither is in supplies, their in-degrees will never reach 0, so they are never added to the queue. No explicit cycle detection is needed.

5. **Only recipes are tracked as results**: Supplies are real ingredients but not answers. Only nodes that appear in `recipes` and reach in-degree 0 are collected.

---

## Solution Explanation

```python
class Solution:
    def findAllRecipes(self, recipes: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        n = len(recipes)
        graph = defaultdict(list)
        in_degree = defaultdict(int)
        for i in range(n):
            for ingredient in ingredients[i]:
                graph[ingredient].append(recipes[i])  # ingredient → recipe
                in_degree[recipes[i]] += 1             # recipe needs one more ingredient
        
        s = set()
        q = deque(supplies)       # start BFS from all initially available supplies
        while q:
            supply = q.popleft()
            for ingredient in graph[supply]:          # for each recipe that needs this supply
                in_degree[ingredient] -= 1            # one dependency satisfied
                if in_degree[ingredient] == 0:        # all dependencies satisfied → can make it
                    q.append(ingredient)              # it becomes a new "supply" for others
                    s.add(ingredient)
        return list(s)
```

**Step-by-step walkthrough (Example 3):**

| State | Queue | Available |
|---|---|---|
| Initial | `[yeast, flour, meat]` | supplies |
| Process `yeast` | `[flour, meat]` | `in_degree[bread]` : 2→1 |
| Process `flour` | `[meat]` | `in_degree[bread]` : 1→0 → enqueue `bread` |
| Process `meat` | `[bread]` | `in_degree[sandwich]` : 2→1, `in_degree[burger]` : 3→2 |
| Process `bread` | `[]` | `in_degree[sandwich]` : 1→0 → enqueue `sandwich`; `in_degree[burger]` : 2→1 |
| Process `sandwich` | `[]` | `in_degree[burger]` : 1→0 → enqueue `burger` |
| Process `burger` | `[]` | done |

Result: `["bread", "sandwich", "burger"]`

**Complexity:**
- Time: $O(V + E)$ where $V$ = total unique ingredient/recipe nodes, $E$ = total edges (ingredient → recipe relationships)
- Space: $O(V + E)$ for the graph and in-degree map
