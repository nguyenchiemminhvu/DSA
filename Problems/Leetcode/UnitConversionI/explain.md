## Problem

https://leetcode.com/problems/unit-conversion-i/description/

```
There are n types of units indexed from 0 to n - 1. You are given a 2D integer array conversions of length n - 1,
where conversions[i] = [sourceUnit_i, targetUnit_i, conversionFactor_i]. This indicates that a single unit of type
sourceUnit_i is equivalent to conversionFactor_i units of type targetUnit_i.

Return an array baseUnitConversion of length n, where baseUnitConversion[i] is the number of units of type i
equivalent to a single unit of type 0. Since the answer may be large, return each baseUnitConversion[i] modulo 10^9 + 7.

Example 1:
Input: conversions = [[0,1,2],[1,2,3]]
Output: [1,2,6]

Example 2:
Input: conversions = [[0,1,2],[0,2,3],[1,3,4],[1,4,5],[2,5,2],[4,6,3],[5,7,4]]
Output: [1,2,3,8,10,6,30,24]

Constraints:
- 2 <= n <= 10^5
- conversions.length == n - 1
- 0 <= sourceUnit_i, targetUnit_i < n
- 1 <= conversionFactor_i <= 10^9
- It is guaranteed that unit 0 can be converted into any other unit through a unique combination of conversions
  without using any conversions in the opposite direction.
```

## Observations

1. **The conversions form a tree rooted at node 0**: There are `n` nodes and exactly `n - 1` directed edges, and the problem guarantees every unit is reachable from unit 0 via a unique path. This is the definition of a rooted tree.

2. **All edges are directed away from root**: Each `conversions[i]` gives a directed edge `sourceUnit -> targetUnit` with a multiplication factor. The guarantee that we never need to traverse an edge in reverse means we only need to follow edges forward from node 0.

3. **The factor for any node = product of all edge weights along the path from node 0 to that node**: If the path from 0 to node `k` passes through edges with factors `f1, f2, ..., fm`, then `baseUnitConversion[k] = f1 * f2 * ... * fm`.

4. **BFS from root propagates factors naturally**: Starting BFS from node 0 with an initial factor of 1, when we traverse an edge `(u -> v)` with weight `w`, the factor for `v` is `factor[u] * w`. This is a simple multiplicative propagation.

5. **Modular arithmetic prevents overflow**: Since conversion factors can be up to `10^9` and paths can be up to `10^5` nodes long, intermediate products are astronomically large. We apply `mod 10^9 + 7` at each multiplication step.

6. **Visited array prevents re-processing**: Because the graph is a tree (directed, no cycles), each node has exactly one parent and will be visited exactly once. The visited array ensures correctness if the input edges are not already in BFS order.

## Solution

**Algorithm**: BFS from node 0, propagating cumulative conversion factors along tree edges.

**Time Complexity**: O(n) — each node and edge is processed exactly once.  
**Space Complexity**: O(n) — for the adjacency list, visited array, factor array, and BFS queue.

**Key Components**:

1. **Build adjacency list** from the conversions:
   ```python
   for u, v, f in conv:
       graph[u].append((f, v))
   ```
   Only directed edges `u -> v` are stored (no reverse edges needed).

2. **BFS traversal** starting from node 0 with factor 1:
   ```python
   q = deque([(1, 0)])   # (cumulative_factor, node)
   visited[0] = True
   while q:
       cur_f, cur_u = q.popleft()
       f_arr[cur_u] = cur_f % mod
       for next_f, next_u in graph[cur_u]:
           if not visited[next_u]:
               visited[next_u] = True
               q.append(((cur_f * next_f) % mod, next_u))
   ```

3. **Factor propagation rule**: When moving from `cur_u` to `next_u` via an edge with weight `next_f`:
   $$\text{factor}[\text{next\_u}] = \text{factor}[\text{cur\_u}] \times \text{next\_f} \pmod{10^9+7}$$

**Step-by-step walkthrough** (Example 2: `[[0,1,2],[0,2,3],[1,3,4],[1,4,5],[2,5,2],[4,6,3],[5,7,4]]`):

```
Graph (adjacency list):
  0 -> [(2, 1), (3, 2)]
  1 -> [(4, 3), (5, 4)]
  2 -> [(2, 5)]
  4 -> [(3, 6)]
  5 -> [(4, 7)]

BFS queue steps:
  Start: q=[(1, 0)], f_arr=[1,1,1,1,1,1,1,1]
  Pop (1, 0):  f_arr[0]=1,  enqueue (1*2=2, 1), (1*3=3, 2)
  Pop (2, 1):  f_arr[1]=2,  enqueue (2*4=8, 3), (2*5=10, 4)
  Pop (3, 2):  f_arr[2]=3,  enqueue (3*2=6, 5)
  Pop (8, 3):  f_arr[3]=8
  Pop (10, 4): f_arr[4]=10, enqueue (10*3=30, 6)
  Pop (6, 5):  f_arr[5]=6,  enqueue (6*4=24, 7)
  Pop (30, 6): f_arr[6]=30
  Pop (24, 7): f_arr[7]=24

Result: [1, 2, 3, 8, 10, 6, 30, 24] ✓
```

## Tags

graph, tree, BFS, modular arithmetic

