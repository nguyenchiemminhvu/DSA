## Problem

https://leetcode.com/problems/minimum-genetic-mutation/description

A gene string can be represented by an 8-character long string with choices from 'A', 'C', 'G', and 'T'.

We need to find the minimum number of mutations to transform a `startGene` into an `endGene`, where:
- One mutation = changing one single character
- A gene is valid only if it exists in the given `bank`
- The starting gene is always valid (may not be in bank)

**Examples:**
- "AACCGGTT" → "AACCGGTA" is one mutation
- startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"] → **Output: 1**
- startGene = "AACCGGTT", endGene = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"] → **Output: 2**

**Constraints:**
- 0 ≤ bank.length ≤ 10
- startGene.length == endGene.length == bank[i].length == 8
- All characters are from ['A', 'C', 'G', 'T']

## Observations

1. **Graph Problem**: This is a shortest path problem where each valid gene is a node, and edges exist between genes that differ by exactly one character.

2. **Valid Transitions**: We can only move between genes that differ in exactly one position (Hamming distance = 1).

3. **End Gene Validation**: If `endGene` is not in the bank, it's impossible to reach it, so return -1.

4. **Edge Cases**:
   - If `startGene == endGene`, the answer is 0 (no mutations needed)
   - If bank is empty or doesn't contain endGene, return -1
   - Bank can have up to 10 genes, so the graph is small

5. **Algorithm Choice**: 
   - With such a small constraint (≤ 10 genes), Floyd-Warshall is viable
   - BFS would be more efficient for this problem (standard shortest path in unweighted graph)
   - The provided solution uses Floyd-Warshall to compute all-pairs shortest paths

## Solution

**Approach**: Floyd-Warshall Algorithm (All-pairs Shortest Path)

The solution builds a weighted graph where:
- Nodes are unique genes (start, end, and all genes in bank)
- Edge weight is 1 if two genes differ by exactly 1 character, 0 if identical
- Floyd-Warshall finds the shortest path from start to end

```python
class Solution:
    def minMutation(self, start: str, end: str, bank: List[str]) -> int:
        # Edge cases
        if start == end:
            return 0
        if end not in bank:
            return -1
        if not bank:
            return -1
        
        # Helper function to count differences between two genes
        def count_diff(a: str, b: str) -> int:
            diff = 0
            for i in range(len(a)):
                diff += 1 if a[i] != b[i] else 0
            return diff

        # Build node list with all unique genes
        arr = list(set([start, end] + bank))
        start_idx = arr.index(start)
        end_idx = arr.index(end)
        
        # Initialize graph with infinity distances
        n = len(arr)
        graph = [[float('inf') for _ in range(n)] for _ in range(n)]
        
        # Build adjacency matrix
        # Edge weight = 1 if genes differ by exactly 1, else 0 or infinity
        for i in range(n):
            for j in range(n):
                if i == j:
                    graph[i][j] = 0  # Same node
                else:
                    diff = count_diff(arr[i], arr[j])
                    if diff == 0:
                        graph[i][j] = 0  # Identical genes
                    elif diff == 1:
                        graph[i][j] = 1  # Valid mutation (1 step)
                    # else: stays as infinity (no direct path)
        
        # Floyd-Warshall algorithm: find all-pairs shortest paths
        # For each intermediate node k
        for mid in range(n):
            # Update all pairs (i, j)
            for i in range(n):
                for j in range(n):
                    if graph[i][mid] != float('inf') and graph[mid][j] != float('inf'):
                        graph[i][j] = min(graph[i][j], graph[i][mid] + graph[mid][j])

        # Return shortest path from start to end
        return -1 if graph[start_idx][end_idx] == float('inf') else graph[start_idx][end_idx]
```

**Time Complexity**: $O(n^3)$ where $n ≤ 11$ (start + end + up to 10 bank items)
- Floyd-Warshall: $O(n^3) = O(1331)$ due to small constraint
- Graph building: $O(n^2 \times 8)$ to compare all gene pairs

**Space Complexity**: $O(n^2)$ for the adjacency matrix

### Key Points:

1. **Graph Construction**: Builds an adjacency matrix where non-connected nodes have infinity distance
2. **Floyd-Warshall Relaxation**: The triple nested loop finds shortest paths through intermediate nodes
3. **Final Answer**: Returns the shortest path distance from start to end index

### Alternative Approach (BFS - More Efficient):

```python
class Solution:
    def minMutation(self, start: str, end: str, bank: List[str]) -> int:
        if end not in bank:
            return -1
        
        def neighbors(gene):
            # Generate all neighbors by changing one character
            chars = ['A', 'C', 'G', 'T']
            for i in range(8):
                for c in chars:
                    if c != gene[i]:
                        yield gene[:i] + c + gene[i+1:]
        
        from collections import deque
        queue = deque([(start, 0)])
        visited = {start}
        bank_set = set(bank)
        
        while queue:
            gene, steps = queue.popleft()
            if gene == end:
                return steps
            
            for neighbor in neighbors(gene):
                if neighbor not in visited and neighbor in bank_set:
                    visited.add(neighbor)
                    queue.append((neighbor, steps + 1))
        
        return -1
```

This BFS approach is more efficient with $O(n \times 8 \times 4)$ complexity since we only explore valid neighbors in the bank.

# Tags
- Graph
- Shortest Path
- Floyd-Warshall
- BFS
- Hamming Distance

