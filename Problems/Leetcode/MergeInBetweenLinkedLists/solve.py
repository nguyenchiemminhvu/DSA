from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        self.next = next

class Solution:
    def mergeInBetween(self, list1: ListNode, a: int, b: int, list2: ListNode) -> ListNode:
        p = ListNode(0, list1)
        while a:
            p = p.next
            a -= 1
            b -= 1
        pp = p
        while b:
            pp = pp.next
            b -= 1
        pp = pp.next
        
        p.next = list2
        while p.next:
            p = p.next
        p.next = pp.next

        return list1