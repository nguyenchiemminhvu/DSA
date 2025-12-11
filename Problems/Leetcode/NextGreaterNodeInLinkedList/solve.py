from typing import Optional, List

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        res = []
        p = head
        while p:
            res.append(0)
            p = p.next
        
        st = [] # (val, i)
        i = 0
        p = head
        while p:
            while st and st[-1][0] < p.val:
                res[st[-1][1]] = p.val
                st.pop()
            st.append((p.val, i))
            i += 1
            p = p.next
        return res