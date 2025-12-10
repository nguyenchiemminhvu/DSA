from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def swapNodes(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        left = right = head
        for i in range(k - 1):
            left = left.next
        
        front = left
        while front.next:
            right = right.next
            front = front.next

        temp = left.val
        left.val = right.val
        right.val = temp

        return head