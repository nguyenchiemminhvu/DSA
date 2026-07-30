from collections import deque
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class CBTInserter:

    def __init__(self, root: Optional[TreeNode]):
        self.root = root
        self.q = deque()

        temp_q = deque([root])
        while temp_q:
            cur = temp_q.popleft()
            if not cur.left or not cur.right:
                self.q.append(cur)
            
            if cur.left:
                temp_q.append(cur.left)
            if cur.right:
                temp_q.append(cur.right)

    def insert(self, val: int) -> int:
        cur = self.q[0]
        new_node = TreeNode(val)
        if not cur.left:
            cur.left = new_node
        else:
            cur.right = new_node
            self.q.popleft()
        
        self.q.append(new_node)
        return cur.val

    def get_root(self) -> Optional[TreeNode]:
        return self.root


# Your CBTInserter object will be instantiated and called as such:
# obj = CBTInserter(root)
# param_1 = obj.insert(val)
# param_2 = obj.get_root()