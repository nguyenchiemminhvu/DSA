from typing import Optional
import unittest

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head == None or head.next == None:
            return head
        
        prev_node = None
        cur_node = head
        next_node = None

        while cur_node != None:
            next_node = cur_node.next
            cur_node.next = prev_node
            prev_node = cur_node
            cur_node = next_node
        return prev_node

class TestReverseLinkedList(unittest.TestCase):
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

    def test_reverseList(self):
        solution = Solution()

        # Test case 1: Normal case
        head = self.list_to_linkedlist([1, 2, 3, 4, 5])
        reversed_head = solution.reverseList(head)
        self.assertEqual(self.linkedlist_to_list(reversed_head), [5, 4, 3, 2, 1])

        # Test case 2: Single element
        head = self.list_to_linkedlist([1])
        reversed_head = solution.reverseList(head)
        self.assertEqual(self.linkedlist_to_list(reversed_head), [1])

        # Test case 3: Empty list
        head = self.list_to_linkedlist([])
        reversed_head = solution.reverseList(head)
        self.assertEqual(self.linkedlist_to_list(reversed_head), [])

        # Test case 4: Two elements
        head = self.list_to_linkedlist([1, 2])
        reversed_head = solution.reverseList(head)
        self.assertEqual(self.linkedlist_to_list(reversed_head), [2, 1])

if __name__ == "__main__":
    unittest.main()