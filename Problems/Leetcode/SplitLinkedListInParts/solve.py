from typing import List, Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def splitListToParts(self, head: Optional[ListNode], k: int) -> List[Optional[ListNode]]:
        arr = []
        while head:
            arr.append(head.val)
            head = head.next
        n = len(arr)

        parts = [[0] * (n // k) for i in range(k)]
        for i in range(n % k):
            parts[i].append(0)

        # fill parts
        ip = 0
        ipp = 0
        for val in arr:
            while not parts[ip] or ipp >= len(parts[ip]):
                ip += 1
                ipp = 0
            if parts[ip] and ipp < len(parts[ip]):
                parts[ip][ipp] = val
                ipp += 1
        
        res = []
        for part in parts:
            head = ListNode(0)
            p = head
            for val in part:
                p.next = ListNode(val)
                p = p.next
            res.append(head.next)
        return res