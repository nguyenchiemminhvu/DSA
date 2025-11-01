from typing import List, Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def modifiedList(self, nums: List[int], head: Optional[ListNode]) -> Optional[ListNode]:
        s = set(nums)
        dummy = ListNode(0, head)
        cur = head
        prev = dummy
        while cur:
            if cur.val in s:
                prev.next = cur.next
                cur = prev.next
            else:
                prev = cur
                cur = cur.next
        return dummy.next