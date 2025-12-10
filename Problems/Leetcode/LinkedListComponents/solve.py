from typing import Optional, List

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def numComponents(self, head: Optional[ListNode], nums: List[int]) -> int:
        s = set(nums)
        count = 0
        while head:
            if head.val in s and (head.next is None or head.next.val not in s):
                count += 1
            head = head.next
        return count