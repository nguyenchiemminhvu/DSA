from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        if k == 1:
            return head
        
        dummy = ListNode(0, head)
        p = dummy
        temp_k = k
        while temp_k > 0 and p:
            p = p.next
            temp_k -= 1
        
        if not p or temp_k > 0:
            return head
        
        next_head = self.reverseKGroup(p.next, k)
        p.next = None
        
        # reverse from head to p
        left, cur, right = next_head, head, None
        while cur:
            right = cur.next
            cur.next = left
            left = cur
            cur = right
        
        return left