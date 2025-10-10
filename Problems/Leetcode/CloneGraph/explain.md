## Problem

https://leetcode.com/problems/clone-graph/

```
Given a reference of a node in a connected undirected graph.

Return a deep copy (clone) of the graph.

Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.

class Node {
    public int val;
    public List<Node> neighbors;
}

Test case format:

For simplicity, each node's value is the same as the node's index (1-indexed). For example, the first node with val == 1, the second node with val == 2, and so on. The graph is represented in the test case using an adjacency list.

An adjacency list is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.

The given node will always be the first node with val = 1. You must return the copy of the given node as a reference to the cloned graph.

Example 1:

Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).

Example 2:

Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.

Example 3:

Input: adjList = []
Output: []
Explanation: This an empty graph, it does not have any nodes.

Constraints:

The number of nodes in the graph is in the range [0, 100].
1 <= Node.val <= 100
Node.val is unique for each node.
There are no repeated edges and no self-loops in the graph.
The Graph is connected and all nodes can be visited starting from the given node.
```

## Observations

1. **Deep Copy Requirement**: We need to create completely new `Node` objects with the same structure, not just copy references.

2. **Graph Traversal**: We need to visit all nodes in the connected graph to clone them. DFS or BFS can be used for traversal.

3. **Cycle Handling**: Since the graph can have cycles (undirected graph), we need to avoid infinite loops during traversal and ensure we don't create duplicate nodes.

4. **Reference Management**: The tricky part is maintaining the correct neighbor relationships in the cloned graph while avoiding creating multiple copies of the same node.

5. **Two-Phase Approach**: The solution uses a clever two-phase approach:
   - Phase 1: Extract the graph structure into an adjacency list
   - Phase 2: Build the cloned graph using the adjacency list

## Solution

The solution employs a **two-phase approach** with DFS:

### Phase 1: Graph Structure Extraction
```python
def dfs(node: Optional['Node']) -> None:
    if node == None:
        return
    if node.val not in adj_list:
        adj_list[node.val] = set()
    for n in node.neighbors:
        if n.val not in adj_list[node.val]:
            adj_list[node.val].add(n.val)
            dfs(n)
```

- **Purpose**: Traverse the original graph and build an adjacency list representation
- **Key Insight**: Extract just the connectivity information (which node connects to which)
- **Cycle Prevention**: Uses `if n.val not in adj_list[node.val]` to avoid revisiting edges
- **Data Structure**: `Dict[int, Set[int]]` maps each node value to its neighbors' values

### Phase 2: Clone Construction
```python
def build_graph(val: int) -> Optional['Node']:
    if val in d:
        return d[val]  # Return already created clone
    root = Node(val)
    d[val] = root      # Store clone immediately to handle cycles
    for adj_val in adj_list[val]:
        root.neighbors.append(build_graph(adj_val))  # Recursive construction
    return root
```

- **Purpose**: Recursively build the cloned graph using the adjacency list
- **Memoization**: Uses dictionary `d` to store already created nodes and avoid duplicates
- **Cycle Safety**: Storing the node in `d` before processing neighbors prevents infinite recursion
- **Reference Integrity**: Each cloned node gets proper references to its cloned neighbors

### Algorithm Flow:
1. **Edge Case**: Return `None` if input is `None`
2. **Extract Structure**: DFS through original graph to build adjacency list
3. **Build Clone**: Recursively create new nodes with proper neighbor relationships
4. **Return**: The cloned version of the starting node

### Time Complexity: O(V + E)
- V = number of vertices, E = number of edges
- Each node and edge is visited once in each phase

### Space Complexity: O(V)
- Adjacency list storage + recursion stack + memoization dictionary

## Tags

graph, dfs, hash table