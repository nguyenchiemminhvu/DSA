from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        stack1 = []
        stack2 = []
        
        # push digits of l1
        while l1:
            stack1.append(l1.val)
            l1 = l1.next
        
        # push digits of l2
        while l2:
            stack2.append(l2.val)
            l2 = l2.next
        
        carry = 0
        head = None  # new list will be built in reverse (from end to start)
        
        # add while there are digits or carry remains
        while stack1 or stack2 or carry:
            x = stack1.pop() if stack1 else 0
            y = stack2.pop() if stack2 else 0
            
            total = x + y + carry
            carry = total // 10
            
            new_node = ListNode(total % 10)
            new_node.next = head
            head = new_node
        
        return head
