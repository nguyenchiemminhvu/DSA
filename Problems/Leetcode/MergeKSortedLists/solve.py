from typing import List, Optional
import heapq

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        global_id = 0

        pq = []
        for p in lists:
            if p:
                heapq.heappush(pq, (p.val, global_id, p.next))
                global_id += 1
        
        res = ListNode() # dummy head
        p = res
        while pq:
            val, _, pnext = heapq.heappop(pq)
            p.next = ListNode(val)
            p = p.next

            if pnext:
                heapq.heappush(pq, (pnext.val, global_id, pnext.next))
                global_id += 1
        
        return res.next