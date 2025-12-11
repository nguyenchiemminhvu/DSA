from typing import Optional, Tuple

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
        def get_pair_node(head: Optional[ListNode], idx: int) -> Tuple[ListNode]:
            prev = head
            cur = head.next
            while idx > 1:
                prev = cur
                cur = cur.next
                idx -= 1
            return (prev, cur)
        
        if not head or not head.next:
            return head
        
        dummy = ListNode(0, head)
        prev_left, p_left = get_pair_node(dummy, left)
        prev_right, p_right = get_pair_node(dummy, right)
        st = []
        p = p_left
        while p != p_right.next:
            st.append(p.val)
            p = p.next
        p = p_left
        while p != p_right.next:
            p.val = st.pop()
            p = p.next
        return head