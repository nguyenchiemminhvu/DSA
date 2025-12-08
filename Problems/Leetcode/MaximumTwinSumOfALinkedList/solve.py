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
        
        arr1 = []
        p = head
        while p:
            arr1.append(p.val)
            p = p.next
        
        p = reverse_list(head)

        arr2 = []
        while p:
            arr2.append(p.val)
            p = p.next
        
        n = len(arr1) // 2
        res = 0
        for i in range(n):
            res = max(res, arr1[i] + arr2[i])
        return res