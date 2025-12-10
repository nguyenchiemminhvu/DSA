from typing import List, Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def spiralMatrix(self, m: int, n: int, head: Optional[ListNode]) -> List[List[int]]:
        grid = [[-1] * n for _ in range(m)]
        r, c = 0, -1
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        idir = 0
        visited = set()
        while head:
            val = head.val
            next_r, next_c = r + directions[idir][0], c + directions[idir][1]
            if next_r >= 0 and next_r < m and next_c >= 0 and next_c < n and (next_r, next_c) not in visited:
                visited.add((next_r, next_c))
                grid[next_r][next_c] = val
                head = head.next
                r, c = next_r, next_c
            else:
                idir = (idir + 1) % 4

        return grid