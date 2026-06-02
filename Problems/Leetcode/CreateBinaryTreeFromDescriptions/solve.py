# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def createBinaryTree(self, desc: List[List[int]]) -> Optional[TreeNode]:
        graph = defaultdict(list)
        roots = set()
        for pa, ch, is_left in desc:
            graph[pa].append((ch, is_left))
            roots.add(pa)
        
        for k, adj in graph.items():
            for node in adj:
                if node[0] in roots:
                    roots.remove(node[0])

        root = list(roots)[0]
        
        def dfs(root_val: int) -> Optional[TreeNode]:
            root = TreeNode(root_val)
            for ch, is_left in graph[root_val]:
                if is_left:
                    root.left = dfs(ch)
                else:
                    root.right = dfs(ch)
            return root

        return dfs(root)