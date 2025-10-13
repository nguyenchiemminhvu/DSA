from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def insertionSortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head == None or head.next == None:
            return head

        dummy = ListNode(-0x7FFFFFFF)
        dummy.next = head
        head = dummy

        cur = head.next.next
        prev = head.next
        while cur:
            key_val = cur.val
            p = head
            before_p = head
            while p != cur and p.val < key_val:
                before_p = p
                p = p.next
            if p != cur:
                # insert cur to before_p.next
                prev.next = cur.next
                cur.next = before_p.next
                before_p.next = cur
                cur = prev.next
            else:
                prev = cur
                cur = cur.next

        return head.next