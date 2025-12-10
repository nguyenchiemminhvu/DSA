from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def sortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        def merge(left: Optional[ListNode], right: Optional[ListNode]) -> Optional[ListNode]:
            dummy = ListNode(-1) # dummy
            p = dummy
            while left and right:
                if left.val <= right.val:
                    p.next = left
                    left = left.next
                else:
                    p.next = right
                    right = right.next
                p = p.next
            
            if left:
                p.next = left
            
            if right:
                p.next = right
            
            return dummy.next
        
        def merge_sort(head: Optional[ListNode]) -> Optional[ListNode]:
            if not head or not head.next:
                return head
            
            slow = fast = head
            prev = None
            while fast and fast.next:
                prev = slow
                slow = slow.next
                fast = fast.next.next
            
            prev.next = None

            left = merge_sort(head)
            right = merge_sort(slow)
            new_head = merge(left, right)
            return new_head
        
        return merge_sort(head)