from collections import deque
from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def minimumOperations(self, root: Optional[TreeNode]) -> int:
        def min_swap_make_sorted(arr: List[int]) -> int:
            n = len(arr)
            mp = {}
            for i in range(n):
                mp[arr[i]] = i
            
            sorted_arr = sorted(arr)

            count_swap = 0
            for sorted_idx in range(n):
                if arr[sorted_idx] != sorted_arr[sorted_idx]:
                    count_swap += 1

                    orig_idx = mp[sorted_arr[sorted_idx]]
                    arr[sorted_idx], arr[orig_idx] = arr[orig_idx], arr[sorted_idx]

                    mp[arr[orig_idx]] = orig_idx
                    mp[arr[sorted_idx]] = sorted_idx
            
            return count_swap
        
        if not root:
            return 0
        
        res = 0
        q = deque([root])
        while q:
            z = len(q)
            row = []
            for _ in range(z):
                cur = q.popleft()
                row.append(cur.val)
                if cur.left:
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)
            
            res += min_swap_make_sorted(row)
        
        return res