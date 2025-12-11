from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        val = 0
        while head:
            val = val * 10 + head.val
            head = head.next
        
        if val == 0:
            return ListNode(0)
        
        val *= 2

        arr = []
        while val:
            arr.append(val % 10)
            val //= 10
        arr.reverse()

        dummy = ListNode(0)
        p = dummy
        for val in arr:
            p.next = ListNode(val)
            p = p.next
        return dummy.next