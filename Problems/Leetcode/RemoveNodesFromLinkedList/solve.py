from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def removeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        def reverse_list(head: Optional[ListNode]) -> Optional[ListNode]:
            a, b, c = None, head, None
            while b:
                c = b.next
                b.next = a
                a = b
                b = c
            return a
        
        head = reverse_list(head)
        p = head
        while p:
            while p.next and p.next.val < p.val:
                p.next = p.next.next
            p = p.next
        head = reverse_list(head)
        return head