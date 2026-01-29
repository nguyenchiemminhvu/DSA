# Minimum Cost to Convert String I

## Problem

https://leetcode.com/problems/minimum-cost-to-convert-string-i/description/

You are given two 0-indexed strings `source` and `target`, both of length `n` and consisting of lowercase English letters. You are also given two 0-indexed character arrays `original` and `changed`, and an integer array `cost`, where `cost[i]` represents the cost of changing the character `original[i]` to the character `changed[i]`.

You start with the string `source`. In one operation, you can pick a character `x` from the string and change it to the character `y` at a cost of `z` if there exists any index `j` such that `cost[j] == z`, `original[j] == x`, and `changed[j] == y`.

Return the minimum cost to convert the string `source` to the string `target` using any number of operations. If it is impossible to convert `source` to `target`, return `-1`.

**Note:** There may exist indices `i`, `j` such that `original[j] == original[i]` and `changed[j] == changed[i]`.

### Examples

**Example 1:**
```
Input: source = "abcd", target = "acbe", 
       original = ["a","b","c","c","e","d"], 
       changed = ["b","c","b","e","b","e"], 
       cost = [2,5,5,1,2,20]
Output: 28
Explanation: To convert "abcd" to "acbe":
- Change index 1: 'b' → 'c' (cost 5)
- Change index 2: 'c' → 'e' (cost 1)
- Change index 2: 'e' → 'b' (cost 2)
- Change index 3: 'd' → 'e' (cost 20)
Total cost: 5 + 1 + 2 + 20 = 28
```

**Example 2:**
```
Input: source = "aaaa", target = "bbbb", 
       original = ["a","c"], 
       changed = ["c","b"], 
       cost = [1,2]
Output: 12
Explanation: 'a' → 'c' → 'b' costs 3 per character
Total: 3 × 4 = 12
```

**Example 3:**
```
Input: source = "abcd", target = "abce", 
       original = ["a"], 
       changed = ["e"], 
       cost = [10000]
Output: -1
Explanation: Cannot convert 'd' to 'e'
```

### Constraints
- `1 <= source.length == target.length <= 10^5`
- `source`, `target` consist of lowercase English letters
- `1 <= cost.length == original.length == changed.length <= 2000`
- `original[i]`, `changed[i]` are lowercase English letters
- `1 <= cost[i] <= 10^6`
- `original[i] != changed[i]`

---

## Observations

1. **Graph Problem**: Each character can be viewed as a node in a graph, and each transformation (original[i] → changed[i]) is a directed edge with weight cost[i].

2. **Shortest Path**: To convert character A to character B, we need the shortest (minimum cost) path in this graph. This might involve intermediate transformations (e.g., A → C → B).

3. **All-Pairs Shortest Path**: Since we have 26 possible characters (a-z) and need to find minimum costs between all pairs, Floyd-Warshall algorithm is ideal.

4. **Multiple Edges**: There can be multiple edges between the same pair of characters with different costs. We should keep only the minimum cost edge.

5. **Independent Conversions**: Each character position in the source string can be converted independently. The total cost is the sum of individual conversion costs.

6. **Impossibility Check**: If the shortest path distance is infinity (no path exists), conversion is impossible.

---

## Solution

### Algorithm: Floyd-Warshall for All-Pairs Shortest Path

**Step 1: Build Initial Graph**
- Create a 26×26 adjacency matrix (one for each lowercase letter)
- Initialize all distances to infinity
- Set diagonal to 0 (no cost to stay same character)
- For each transformation rule, set `graph[original[i]][changed[i]]` to the minimum cost if multiple rules exist

**Step 2: Floyd-Warshall Algorithm**
```
For each intermediate node k:
    For each source node i:
        For each target node j:
            If path i → k → j is shorter than direct path i → j:
                Update graph[i][j] = graph[i][k] + graph[k][j]
```

This finds the minimum cost path between all pairs of characters.

**Step 3: Calculate Total Conversion Cost**
- Iterate through each position in source and target
- If characters match, no cost needed
- Otherwise, look up the minimum cost from `graph[source[i]][target[i]]`
- If cost is infinity, return -1 (impossible)
- Sum all costs

### Time Complexity
- **Graph Construction**: O(G) where G = len(cost) ≈ 2000
- **Floyd-Warshall**: O(26³) = O(17,576) = O(1) constant
- **Cost Calculation**: O(N) where N = len(source)
- **Total**: O(G + N) ≈ O(N) since N can be up to 10⁵

### Space Complexity
- O(26²) = O(676) = O(1) for the graph

### Code Implementation

```python
class Solution:
    def minimumCost(self, source: str, target: str, 
                    original: List[str], changed: List[str], 
                    cost: List[int]) -> int:
        n = len(source)
        ng = len(cost)
        
        # Step 1: Initialize graph with infinity
        graph = [[float('inf')] * 26 for _ in range(26)]
        
        # No cost to convert a character to itself
        for i in range(26):
            graph[i][i] = 0
        
        # Build the graph with minimum costs for direct transformations
        for i in range(ng):
            sval = ord(original[i]) - ord('a')  # Convert char to index 0-25
            star = ord(changed[i]) - ord('a')
            # Keep minimum cost if multiple edges exist
            graph[sval][star] = min(graph[sval][star], cost[i])
        
        # Step 2: Floyd-Warshall - find all-pairs shortest paths
        for inter in range(26):  # Intermediate node
            for a in range(26):    # Source node
                for b in range(26):  # Target node
                    # Avoid overflow by checking infinity
                    if graph[a][inter] != float('inf') and graph[inter][b] != float('inf'):
                        # Relax the edge if shorter path found
                        if graph[a][inter] + graph[inter][b] < graph[a][b]:
                            graph[a][b] = graph[a][inter] + graph[inter][b]
        
        # Step 3: Calculate total cost for conversion
        total_cost = 0
        for i in range(n):
            # No change needed if characters already match
            if source[i] == target[i]:
                continue
            
            sval = ord(source[i]) - ord('a')
            star = ord(target[i]) - ord('a')
            dist = graph[sval][star]
            
            # Impossible to convert if no path exists
            if dist == float('inf'):
                return -1
            
            total_cost += dist
        
        return total_cost
```

### Example Trace: Example 1

**Input:**
- source = "abcd", target = "acbe"
- original = ["a","b","c","c","e","d"]
- changed = ["b","c","b","e","b","e"]
- cost = [2,5,5,1,2,20]

**Graph After Initial Build:**
```
a → b: 2
b → c: 5
c → b: 5
c → e: 1
e → b: 2
d → e: 20
```

**After Floyd-Warshall (some derived paths):**
```
Direct edges remain, but we can find cheaper paths:
c → b: min(5, c→e→b) = min(5, 1+2) = 3
b → e: b→c→e = 5+1 = 6
a → c: a→b→c = 2+5 = 7
a → e: a→b→c→e = 2+5+1 = 8
... etc
```

**Conversion Cost Calculation:**
```
Position 0: 'a' → 'a' ✓ cost = 0
Position 1: 'b' → 'c' ✓ cost = 5
Position 2: 'c' → 'b' ✓ cost = 3 (via c→e→b)
Position 3: 'd' → 'e' ✓ cost = 20

Total = 0 + 5 + 3 + 20 = 28 ✓
```

---

## Key Takeaways

1. **Recognize the pattern**: Character transformation with costs → Graph shortest path problem
2. **Choose the right algorithm**: Multiple queries for shortest paths → Floyd-Warshall
3. **Handle edge cases**: 
   - Multiple edges between same nodes (keep minimum)
   - Impossible conversions (return -1)
   - Characters already matching (skip, cost 0)
4. **Optimization**: Pre-compute all shortest paths once, then O(1) lookup per character

# Tags

`Graph` `Shortest Path` `Floyd-Warshall` `Dynamic Programming` `String`

