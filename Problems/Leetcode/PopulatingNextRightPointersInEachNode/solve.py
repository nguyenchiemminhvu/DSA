from typing import Optional

# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next

class Solution:
    def connect(self, root: 'Optional[Node]') -> 'Optional[Node]':
        if root == None:
            return None

        rows = []

        Q = [root]
        while len(Q) > 0:
            cur_len = len(Q)
            row = []
            while cur_len:
                cur_node = Q.pop(0)
                cur_len -= 1
                row.append(cur_node)
                if cur_node.left:
                    Q.append(cur_node.left)
                if cur_node.right:
                    Q.append(cur_node.right)
            rows.append(row)
        
        for row in rows:
            for i in range(1, len(row)):
                row[i-1].next = row[i]
        
        return root