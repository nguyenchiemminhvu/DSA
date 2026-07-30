from collections import deque
import heapq
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        pq = []

        q = deque([root])
        while q:
            sum_row = 0
            for _ in range(len(q)):
                cur = q.popleft()
                sum_row += cur.val
                if cur.left:
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)
            heapq.heappush(pq, sum_row)
            if len(pq) > k:
                heapq.heappop(pq)
        
        return -1 if len(pq) < k else heapq.heappop(pq)