from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def recoverFromPreorder(self, traversal: str) -> Optional[TreeNode]:
        n = len(traversal)
        i = 0

        root = None
        st = []
        while i < n:
            depth = 0
            while i < n and traversal[i] == '-':
                depth += 1
                i += 1
            
            val = 0
            while i < n and traversal[i].isdigit():
                d = int(traversal[i])
                val = val * 10 + d
                i += 1
            
            node = TreeNode(val)
            if depth == 0:
                root = node

            while len(st) > depth:
                st.pop()

            if st:
                parent = st[-1]
                if not parent.left:
                    parent.left = node
                elif not parent.right:
                    parent.right = node

            st.append(node)
        
        return root