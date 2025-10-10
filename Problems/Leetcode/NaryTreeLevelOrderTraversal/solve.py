from collections import deque
from typing import List, Optional

class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children

class Solution:
    def levelOrder(self, root: 'Node') -> List[List[int]]:
        def traversal(root: 'Node', arr: List[List[int]]) -> None:
            if root == None:
                return
            q = deque([root])
            while len(q) > 0:
                cur_len = len(q)
                row = []
                for _ in range(cur_len):
                    cur_node = q.popleft()
                    row.append(cur_node.val)
                    for child in cur_node.children:
                        q.append(child)
                arr.append(row)
        
        arr = []
        traversal(root, arr)
        return arr