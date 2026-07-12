## Problem

https://leetcode.com/problems/path-with-maximum-probability/description/

Given an undirected weighted graph of `n` nodes (0-indexed), represented by an edge list where `edges[i] = [a, b]` is an undirected edge connecting nodes `a` and `b` with a probability of success `succProb[i]` for traversing that edge.

Given two nodes `start` and `end`, find the path with the **maximum probability** of success to go from `start` to `end` and return its success probability.

- If there is no path, return `0`.
- The probability of a path is the **product** of the probabilities of all edges along the path.

**Constraints:**
- `2 <= n <= 10^4`
- `0 <= succProb.length == edges.length <= 2 * 10^4`
- `0 <= succProb[i] <= 1`

---

## Observations

1. **Product, not sum**: The probability of a path is the product of edge probabilities. We want to maximize this product.

2. **Analogy to shortest path**: This is structurally identical to Dijkstra's shortest path algorithm, but instead of minimizing a sum, we are **maximizing a product**. Since all probabilities are in `[0, 1]`, multiplying them together never increases the value — so greedy expansion from the highest-probability frontier is correct.

3. **Max-heap via negation**: Python's `heapq` is a min-heap. To simulate a max-heap, we negate the probability values when pushing and negate again when popping.

4. **Early termination**: Once we pop `end_node` from the heap, its probability is finalized (similar to Dijkstra). We can return early at that point (though the code here just completes naturally via `dp[end_node]`).

5. **Stale entry pruning**: Because we may push the same node multiple times with updated (higher) probabilities, we check `if cur_p < dp[u]: continue` to skip outdated heap entries.

---

## Solution Explanation

```python
class Solution:
    def maxProbability(self, n: int, edges: List[List[int]], probs: List[float], start_node: int, end_node: int) -> float:
        graph = defaultdict(list)
        for i in range(len(edges)):
            u, v = edges[i]
            p = probs[i]
            graph[u].append((-p, v))   # store negated for max-heap simulation
            graph[v].append((-p, u))

        dp = [0.0] * n       # dp[i] = best known probability to reach node i
        dp[start_node] = 1.0

        pq = [(-1.0, start_node)]   # max-heap: push (-prob, node)
        while pq:
            cur_p, u = heapq.heappop(pq)
            cur_p *= -1.0            # restore actual probability

            if cur_p < dp[u]:        # stale entry — a better path was already found
                continue

            for p, v in graph[u]:    # p is stored negated in graph
                if dp[v] < cur_p * -p:        # -p restores actual edge probability
                    dp[v] = cur_p * -p
                    heapq.heappush(pq, (-dp[v], v))

        return dp[end_node]
```

**Step-by-step:**

1. **Build adjacency list**: For each edge `(u, v, p)`, store `(-p, v)` in `graph[u]` and `(-p, u)` in `graph[v]`. Probabilities are negated upfront so that `cur_p * -p` correctly computes the product.

2. **Initialize `dp`**: All nodes start at probability `0.0`, except `start_node` which is `1.0` (100% chance to "reach" where we already are).

3. **Dijkstra loop**:
   - Pop the node `u` with the current highest probability `cur_p` from the heap.
   - Skip if `cur_p` is less than `dp[u]` (stale entry from an older, worse push).
   - For each neighbor `v`, compute `new_prob = cur_p * (-p)` (the `-p` un-negates the stored value). If this exceeds `dp[v]`, update and push to the heap.

4. **Return `dp[end_node]`**, which holds the maximum probability path from `start` to `end` (or `0.0` if unreachable).

**Time complexity**: `O((V + E) log V)` — same as Dijkstra.  
**Space complexity**: `O(V + E)` for the graph and dp array.
