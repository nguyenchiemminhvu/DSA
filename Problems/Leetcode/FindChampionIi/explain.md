## Problem

https://leetcode.com/problems/find-champion-ii/description/

```
There are n teams numbered from 0 to n - 1 in a tournament; each team is also a node in a DAG.

You are given the integer n and a 0-indexed 2D integer array edges of length m representing the DAG, where edges[i] = [ui, vi] indicates that there is a directed edge from team ui to team vi in the graph.

A directed edge from a to b in the graph means that team a is stronger than team b and team b is weaker than team a.

Team a will be the champion of the tournament if there is no team b that is stronger than team a.

Return the team that will be the champion of the tournament if there is a unique champion, otherwise, return -1.

Notes
- A cycle is a series of nodes a1, a2, ..., an, an+1 such that node a1 is the same node as node an+1, the nodes a1, a2, ..., an are distinct, and there is a directed edge from node ai to node ai+1 for every i in [1, n].
- A DAG is a directed graph that does not have any cycle.

Example 1:

Input: n = 3, edges = [[0,1],[1,2]]
Output: 0
Explanation: Team 1 is weaker than team 0. Team 2 is weaker than team 1. So the champion is team 0.

Example 2:

Input: n = 4, edges = [[0,2],[1,3],[1,2]]
Output: -1
Explanation: Team 2 is weaker than team 0 and team 1. Team 3 is weaker than team 1. But team 1 and team 0 are not weaker than any other teams. So the answer is -1.

Constraints:
- 1 <= n <= 100
- m == edges.length
- 0 <= m <= n * (n - 1) / 2
- edges[i].length == 2
- 0 <= edge[i][j] <= n - 1
- edges[i][0] != edges[i][1]
- The input is generated such that if team a is stronger than team b, team b is not stronger than team a.
- The input is generated such that if team a is stronger than team b and team b is stronger than team c, then team a is stronger than team c.
```

## Observations

1. **Graph Representation**: The tournament is expressed as a DAG. An edge `u -> v` means team `u` is stronger than team `v`.

2. **Champion = Source Node**: Team `a` is a champion iff no team is stronger than it. In graph terms, no edge points into `a` — its **in-degree is 0**.

3. **Counting In-Degrees Is Enough**: Because the graph is a DAG and the strength relation is transitive, every non-champion team must have at least one incoming edge from some stronger team. We don't need to traverse paths — a single pass over `edges` to count in-degrees suffices.

4. **Uniqueness Check**: A unique champion exists iff **exactly one** node has in-degree 0. If two or more such nodes exist, none dominates the others (there is no edge between them in either direction), so the champion is ambiguous → return `-1`.

5. **At Least One Source Exists**: Every DAG has at least one node with in-degree 0, so we never need to handle the "zero candidates" case.

## Solution

```python
class Solution:
    def findChampion(self, n: int, edges: List[List[int]]) -> int:
        mp = defaultdict(int)
        for u, v in edges:
            mp[v] += 1

        cand = -1
        for i in range(n):
            if mp[i] == 0:
                if cand != -1:
                    return -1
                cand = i

        return cand
```

**Step-by-step:**

1. **Build In-Degree Map**: Iterate over `edges`. For each edge `[u, v]`, increment `mp[v]`. After the loop, `mp[i]` holds the number of teams stronger than team `i`.

2. **Scan Teams For Sources**: Iterate `i` from `0` to `n - 1`:
   - If `mp[i] == 0`, team `i` has no one stronger than it — a champion candidate.
   - If `cand != -1` already, two zero-in-degree teams exist → the champion is not unique → return `-1` immediately.
   - Otherwise, record `cand = i`.

3. **Return Result**: After the scan, `cand` is the only team with in-degree 0 and is returned as the unique champion.

**Why This Works:**
- Transitivity guarantees that if two teams both have in-degree 0, neither is stronger than the other (no edge in either direction), so neither qualifies as the unique champion.
- Conversely, if only one node has in-degree 0, transitivity implies that node has a path to every other node, i.e. it is stronger than all the rest.

**Time Complexity:** O(n + m) — one pass over edges, one pass over the `n` teams.

**Space Complexity:** O(n) — the in-degree map stores up to `n` entries.

**Example Walkthrough:**

For `n = 4, edges = [[0,2],[1,3],[1,2]]`:
- In-degrees: `mp = {2: 2, 3: 1}`; teams 0 and 1 have in-degree 0.
- Scan: `i = 0` → `cand = 0`. `i = 1` → another zero with `cand != -1` → return `-1`.

For `n = 3, edges = [[0,1],[1,2]]`:
- In-degrees: `mp = {1: 1, 2: 1}`; only team 0 has in-degree 0.
- Scan: `i = 0` → `cand = 0`. `i = 1, 2` → non-zero. Return `0`.

# Tags

#graph #dag #in-degree #topological-sort #greedy
