from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        s = 0
        new_head = ListNode(0)
        p_head = new_head
        while head:
            if head.val == 0:
                if s > 0:
                    p_head.next = ListNode(s)
                    p_head = p_head.next
                s = 0
            else:
                s += head.val
            head = head.next
        return new_head.next