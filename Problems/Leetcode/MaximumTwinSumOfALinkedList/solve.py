from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def pairSum(self, head: Optional[ListNode]) -> int:
        def reverse_list(head: Optional[ListNode]) -> Optional[ListNode]:
            a = None
            b = head
            c = None
            while b:
                c = b.next
                b.next = a
                a = b
                b = c
            return a
        
        slow = head
        fast = head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        
        head_head = slow.next
        slow.next = None

        head_head = reverse_list(head_head)

        res = 0
        while head and head_head:
            val = head.val + head_head.val
            res = max(res, val)
            head = head.next
            head_head = head_head.next
        return res