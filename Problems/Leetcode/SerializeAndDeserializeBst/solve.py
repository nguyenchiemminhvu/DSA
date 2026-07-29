from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Codec:

    def serialize(self, root: Optional[TreeNode]) -> str:
        """Encodes a tree to a single string.
        """
        def dfs(root):
            if not root:
                return '#'
            s = str(root.val)
            s += ','
            s += dfs(root.left)
            s += ','
            s += dfs(root.right)
            return s
        
        return dfs(root)
        

    def deserialize(self, data: str) -> Optional[TreeNode]:
        """Decodes your encoded data to tree.
        """
        arr = iter(data.split(','))
        def dfs():
            val = next(arr)
            if val == '#':
                return None
            
            root = TreeNode(int(val))
            root.left = dfs()
            root.right = dfs()
            return root
        
        return dfs()

# Your Codec object will be instantiated and called as such:
# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# tree = ser.serialize(root)
# ans = deser.deserialize(tree)
# return ans