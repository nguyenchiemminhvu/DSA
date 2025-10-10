from typing import Dict, Set

# Definition for a Node.
class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

from typing import Optional
class Solution:
    def cloneGraph(self, node: Optional['Node']) -> Optional['Node']:
        if node == None:
            return None

        adj_list: Dict[int, Set[int]] = {} # vertex id -> set of vertex id
        
        def dfs(node: Optional['Node']) -> None:
            if node == None:
                return
            if node.val not in adj_list:
                adj_list[node.val] = set()
            for n in node.neighbors:
                if n.val not in adj_list[node.val]:
                    adj_list[node.val].add(n.val)
                    dfs(n)
        
        d = {}
        def build_graph(val:int) -> Optional['Node']:
            if val in d:
                return d[val]
            root = Node(val)
            d[val] = root
            for adj_val in adj_list[val]:
                root.neighbors.append(build_graph(adj_val))
            return root
        
        dfs(node)
        return build_graph(node.val)