from typing import Optional
from typing import List

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def partition(self, head: Optional[ListNode], x: int) -> Optional[ListNode]:
        left = ListNode(float('inf'))
        right = ListNode(float('inf'))
        pleft = left
        pright = right
        while head:
            if head.val < x:
                pleft.next = head
                pleft = pleft.next
            else:
                pright.next = head
                pright = pright.next
            head = head.next
        pleft.next = None
        pright.next = None

        head = left.next
        if not head:
            head = right.next
        else:
            while left.next:
                left = left.next
            left.next = right.next
        return head