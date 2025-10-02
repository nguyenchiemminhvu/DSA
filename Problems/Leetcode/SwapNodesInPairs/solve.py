from typing import Optional
import unittest

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head == None or head.next == None:
            return head
        
        head.next.next = self.swapPairs(head.next.next)
        temp = head.next
        head.next = head.next.next
        temp.next = head
        return temp

class TestSwapNodesInPairs(unittest.TestCase):
    def list_to_linkedlist(self, lst):
        if not lst:
            return None
        head = ListNode(lst[0])
        current = head
        for value in lst[1:]:
            current.next = ListNode(value)
            current = current.next
        return head

    def linkedlist_to_list(self, node):
        lst = []
        while node:
            lst.append(node.val)
            node = node.next
        return lst

    def test_swapPairs(self):
        sol = Solution()
        
        # Test case 1
        head = self.list_to_linkedlist([1, 2, 3, 4])
        expected = [2, 1, 4, 3]
        result = sol.swapPairs(head)
        self.assertEqual(self.linkedlist_to_list(result), expected)
        
        # Test case 2
        head = self.list_to_linkedlist([])
        expected = []
        result = sol.swapPairs(head)
        self.assertEqual(self.linkedlist_to_list(result), expected)
        
        # Test case 3
        head = self.list_to_linkedlist([1])
        expected = [1]
        result = sol.swapPairs(head)
        self.assertEqual(self.linkedlist_to_list(result), expected)
        
        # Test case 4
        head = self.list_to_linkedlist([1, 2, 3])
        expected = [2, 1, 3]
        result = sol.swapPairs(head)
        self.assertEqual(self.linkedlist_to_list(result), expected)

if __name__ == "__main__":
    unittest.main()