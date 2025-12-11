from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
        def reverse_list(head: Optional[ListNode]) -> Optional[ListNode]:
            back = None
            cur = head
            while cur:
                front = cur.next
                cur.next = back
                back = cur
                cur = front
            return back
        
        arr = []
        p = head
        n = 1
        while p:
            count = 1
            phead = p
            while p and count < n:
                count += 1
                p = p.next
            
            if not p or count < n:
                arr.append(phead)
                break
            else:
                temp = p
                p = p.next
                temp.next = None
                arr.append(phead)
            n += 1
        
        for i in range(len(arr)):
            p = arr[i]
            count = 0
            while p:
                count += 1
                p = p.next
            if arr[i] and count % 2 == 0:
                p = reverse_list(arr[i])
                arr[i] = p
        
        head = arr[0]
        for i in range(0, len(arr) - 1):
            p = arr[i]
            while p.next:
                p = p.next
            p.next = arr[i + 1]
        return head