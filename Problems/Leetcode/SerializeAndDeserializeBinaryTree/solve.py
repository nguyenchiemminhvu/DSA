from typing import List, Optional

# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        if root == None:
            return '#'
        return str(root.val) + ',' + self.serialize(root.left) + ',' + self.serialize(root.right)

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        def deserialize_internal(nodes: List[str]) -> Optional[TreeNode]:
            if nodes[0] == "#":
                nodes.pop(0)
                return None
            root = TreeNode(int(nodes[0]))
            nodes.pop(0)
            root.left = deserialize_internal(nodes)
            root.right = deserialize_internal(nodes)
            return root
        
        nodes = data.split(',')
        return deserialize_internal(nodes)

# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# ans = deser.deserialize(ser.serialize(root))