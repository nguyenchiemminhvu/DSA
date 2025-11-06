## Problem

https://leetcode.com/problems/power-grid-maintenance/description/

```
You are given an integer c representing c power stations, each with a unique identifier id from 1 to c (1‑based indexing).

These stations are interconnected via n bidirectional cables, represented by a 2D array connections, where each element connections[i] = [ui, vi] indicates a connection between station ui and station vi. Stations that are directly or indirectly connected form a power grid.

Initially, all stations are online (operational).

You are also given a 2D array queries, where each query is one of the following two types:

[1, x]: A maintenance check is requested for station x. If station x is online, it resolves the check by itself. If station x is offline, the check is resolved by the operational station with the smallest id in the same power grid as x. If no operational station exists in that grid, return -1.

[2, x]: Station x goes offline (i.e., it becomes non-operational).

Return an array of integers representing the results of each query of type [1, x] in the order they appear.

Note: The power grid preserves its structure; an offline (non‑operational) node remains part of its grid and taking it offline does not alter connectivity.

Example 1:

Input: c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]

Output: [3,2,3]

Explanation:

Initially, all stations {1, 2, 3, 4, 5} are online and form a single power grid.
Query [1,3]: Station 3 is online, so the maintenance check is resolved by station 3.
Query [2,1]: Station 1 goes offline. The remaining online stations are {2, 3, 4, 5}.
Query [1,1]: Station 1 is offline, so the check is resolved by the operational station with the smallest id among {2, 3, 4, 5}, which is station 2.
Query [2,2]: Station 2 goes offline. The remaining online stations are {3, 4, 5}.
Query [1,2]: Station 2 is offline, so the check is resolved by the operational station with the smallest id among {3, 4, 5}, which is station 3.

Example 2:

Input: c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]

Output: [1,-1]

Explanation:

There are no connections, so each station is its own isolated grid.
Query [1,1]: Station 1 is online in its isolated grid, so the maintenance check is resolved by station 1.
Query [2,1]: Station 1 goes offline.
Query [1,1]: Station 1 is offline and there are no other stations in its grid, so the result is -1.

Constraints:

1 <= c <= 105
0 <= n == connections.length <= min(105, c * (c - 1) / 2)
connections[i].length == 2
1 <= ui, vi <= c
ui != vi
1 <= queries.length <= 2 * 105
queries[i].length == 2
queries[i][0] is either 1 or 2.
1 <= queries[i][1] <= c
```

## Observations

1. **Core Problem Structure:**
   - We have `c` power stations (1-indexed) connected by cables forming power grids
   - Need to process two types of queries:
     - Type 1: Maintenance check on station `x` → return operational station with smallest ID in same grid
     - Type 2: Take station `x` offline
   - If station is online during maintenance check, it resolves itself
   - If station is offline, find smallest ID operational station in same connected component

2. **Key Insights:**
   - This is a **Union-Find (Disjoint Set Union)** problem with dynamic queries
   - Connected components represent power grids
   - Need to efficiently find the smallest available station in each component
   - Stations going offline don't break connectivity structure (important note in problem)

3. **Data Structure Requirements:**
   - **DSU** to track connected components (power grids)
   - **Min-heap per component** to efficiently get smallest operational station
   - **Set to track offline stations** for quick lookup

4. **Algorithm Strategy:**
   - Build initial DSU from connections
   - For each component, maintain a min-heap of all stations in that component
   - Process queries:
     - Type 1: Check if station is offline, if yes find smallest operational station in same component
     - Type 2: Mark station as offline
   - Use lazy deletion from heaps (pop offline stations as needed)

5. **Edge Cases:**
   - Station requested is online → return itself
   - All stations in a component are offline → return -1
   - Isolated stations (no connections) → each forms its own component

## Solution

### Approach: Union-Find with Min-Heaps

The solution uses **Disjoint Set Union (DSU)** to group stations into connected components and maintains **min-heaps** for each component to efficiently find the smallest operational station.

**Algorithm:**

1. **Initialize DSU**: Create DSU for `c` stations (0-indexed internally)

2. **Build Components**: Process all connections to form connected components

3. **Create Min-Heaps**: For each component, create a min-heap containing all station IDs in that component

4. **Process Queries**:
   - **Type 1 [1, x]**: Maintenance check
     - If station `x-1` is not offline → return `x`
     - Otherwise, find root of component containing `x-1`
     - Pop offline stations from component's heap until finding operational station
     - Return smallest operational station + 1 (convert back to 1-indexed)
   - **Type 2 [2, x]**: Add `x-1` to offline set

**Key Implementation Details:**

```python
class DSU:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.rank = [0] * n
        self.size = n
    
    def find(x: int) -> int:
        # Path compression for efficiency
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def unite(x: int, y: int) -> None:
        # Union by rank for balanced tree
        root_x, root_y = self.find(x), self.find(y)
        if root_x != root_y:
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_y] = root_x
            elif self.rank[root_x] > self.rank[root_y]:
                self.parent[root_x] = root_y
            else:
                self.parent[root_y] = root_x
                self.rank[root_y] += 1
```

**Lazy Deletion Strategy:**
- Instead of removing stations from heaps when they go offline, we use lazy deletion
- When processing Type 1 queries, pop offline stations from heap until finding operational one
- This avoids expensive heap deletion operations

**Time Complexity:**
- DSU operations: O(α(n)) per operation (nearly constant)
- Building components: O(n × α(n))
- Processing queries: O(q × log(c)) worst case per query
- Overall: O((n + q) × log(c))

**Space Complexity:**
- DSU: O(c)
- Heaps: O(c) total across all components
- Offline set: O(q)
- Overall: O(c + q)

**Why This Works:**
- DSU efficiently manages connected components
- Min-heaps provide O(log n) access to smallest elements
- Lazy deletion avoids expensive heap maintenance
- Offline set provides O(1) lookup for station status

# Tags

Union-Find, Disjoint Set Union, Min-Heap, Connected Components, Graph Theory, Lazy Deletion

