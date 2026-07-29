## Problem

https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/description/

You are given the **root** of a binary tree with unique values, and an integer **start**. At minute 0, an infection starts from the node with value `start`.

Each minute, a node becomes infected if:
- The node is currently **uninfected**.
- The node is **adjacent** to an infected node (parent, left child, or right child).

Return the **number of minutes** needed for the entire tree to be infected.

**Example 1:**
```
Input: root = [1,5,3,null,4,10,6,9,2], start = 3
Output: 4
```
- Minute 0: Node 3
- Minute 1: Nodes 1, 10, 6
- Minute 2: Node 5
- Minute 3: Node 4
- Minute 4: Nodes 9 and 2

**Example 2:**
```
Input: root = [1], start = 1
Output: 0
```

**Constraints:**
- Number of nodes in `[1, 10^5]`
- `1 <= Node.val <= 10^5`
- All node values are unique.
- A node with value `start` exists in the tree.

---

## Observations

1. **The infection spreads to all adjacent nodes each minute — this is BFS on a graph.**  
   A binary tree only has parent→child edges, but infection can travel *upward* (child → parent) as well as downward. The tree must therefore be treated as an **undirected graph**.

2. **The answer equals the BFS depth (number of levels) starting from `start` in the undirected graph.**  
   BFS naturally models the simultaneous spread to all neighbors each minute.

3. **Two-phase approach:**
   - **Phase 1 — Build an undirected adjacency map** from the tree. For every node, record its parent, left child, and right child as neighbors.
   - **Phase 2 — Run BFS from `start`** and count the number of levels processed (minutes elapsed).

4. **The answer is `levels - 1`** (since level 0 is the start node itself and we count transitions, not layers). Equivalently, track a `time` counter and increment it for each BFS round that processes at least one new node.

5. **Alternative — DFS to find the longest path from `start`.**  
   During a post-order DFS we can compute, for each subtree, the maximum depth reachable within that subtree. When we find the `start` node we also factor in the distance traveling *up* through the ancestor chain. The final answer is the maximum path length ever seen.

---

## Solution

### Approach 1: Convert to Graph + BFS

**Steps:**
1. Walk the tree once (DFS/BFS) to build an adjacency list `graph: {val → [neighbors]}`.
2. Run a standard BFS from `start`, tracking visited nodes.
3. Every time the BFS queue moves to the next level, increment `time`.
4. Return `time`.

```python
from collections import defaultdict, deque
from typing import Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def amountOfTime(self, root: Optional[TreeNode], start: int) -> int:
        # Phase 1: build undirected graph
        graph = defaultdict(list)

        def build(node, parent):
            if not node:
                return
            if parent:
                graph[node.val].append(parent.val)
                graph[parent.val].append(node.val)
            build(node.left, node)
            build(node.right, node)

        build(root, None)

        # Phase 2: BFS from start
        visited = {start}
        queue = deque([start])
        time = -1

        while queue:
            time += 1
            for _ in range(len(queue)):
                node = queue.popleft()
                for neighbor in graph[node]:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)

        return time
```

**Walkthrough for Example 1** (`start = 3`):

| Minute | Queue (before processing) | Newly infected |
|--------|--------------------------|----------------|
| 0      | [3]                      | 3              |
| 1      | [1, 10, 6]               | 1, 10, 6       |
| 2      | [5]                      | 5              |
| 3      | [4]                      | 4              |
| 4      | [9, 2]                   | 9, 2           |

`time = 4` ✓

**Complexity:** $O(N)$ time and $O(N)$ space (graph + BFS queue).

---

### Approach 2: Single-pass DFS (no extra graph)

During a DFS we compute, for every subtree, two things:
- `depth`: the maximum depth reachable *inside* this subtree from the root of the subtree.
- Whether `start` lives inside this subtree, and if so, how deep it is.

When processing a node `u`:
- If `start` is **not** in the current subtree, return the normal max depth downward.
- If `start` **is** in the current subtree (found in left or right child), we know the infection can also travel upward from `start`. The path that goes up through `u` and down the *other* branch is a candidate for the answer:
  $$\text{ans} = \max(\text{ans},\ \text{dist\_from\_start\_to\_u} + \text{depth\_of\_other\_branch})$$

```python
class Solution:
    def amountOfTime(self, root: Optional[TreeNode], start: int) -> int:
        self.ans = 0

        def dfs(node) -> int:
            """
            Returns:
              >= 0  : max depth of this subtree (start NOT found here)
              < 0   : -(distance from start to this node's root) - 1
                      i.e. start IS in this subtree; negative encodes distance
            """
            if not node:
                return 0

            left = dfs(node.left)
            right = dfs(node.right)

            if node.val == start:
                # depth downward from start
                depth = max(left if left >= 0 else -left - 1,
                            right if right >= 0 else -right - 1)
                self.ans = max(self.ans, depth)
                return -1   # distance from start to itself = 0, encode as -1

            if left < 0:
                # start is in left subtree, distance from start to current node
                dist = -left          # -left - 1 + 1
                # path: go up through current node, then down right subtree
                self.ans = max(self.ans, dist + max(right, 0))
                return -(dist + 1)    # propagate upward

            if right < 0:
                dist = -right
                self.ans = max(self.ans, dist + max(left, 0))
                return -(dist + 1)

            # start not in this subtree
            return 1 + max(left, right)

        dfs(root)
        return self.ans
```

**Complexity:** $O(N)$ time, $O(H)$ space for the call stack (where $H$ is the tree height).

---

## Comparison

| | Approach 1 (Graph + BFS) | Approach 2 (DFS only) |
|---|---|---|
| Time | $O(N)$ | $O(N)$ |
| Extra space | $O(N)$ (graph) | $O(H)$ (stack) |
| Code clarity | High — straightforward BFS | Moderate — negative encoding is tricky |
| Best for | Interview explanation | Space-optimized solution |

---

# Tags

`Binary Tree` `BFS` `DFS` `Graph` `Tree Traversal`

