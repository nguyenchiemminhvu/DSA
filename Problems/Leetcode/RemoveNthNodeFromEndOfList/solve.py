from typing import Optional
import unittest

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        slow = dummy
        fast = dummy
        temp = n
        while temp > 0 and fast:
            temp -= 1
            fast = fast.next

        if fast == None:
            return head
        
        temp = n
        while fast and fast.next:
            fast = fast.next
            slow = slow.next
        slow.next = slow.next.next
        return dummy.next

class TestRemoveNthNodeFromEndOfList(unittest.TestCase):
    def list_to_linkedlist(self, lst):
        dummy = ListNode(0)
        current = dummy
        for value in lst:
            current.next = ListNode(value)
            current = current.next
        return dummy.next

    def linkedlist_to_list(self, node):
        lst = []
        while node:
            lst.append(node.val)
            node = node.next
        return lst

    def test_cases(self):
        solution = Solution()

        # Test case 1
        head = self.list_to_linkedlist([1, 2, 3, 4, 5])
        n = 2
        expected = [1, 2, 3, 5]
        result = solution.removeNthFromEnd(head, n)
        self.assertEqual(self.linkedlist_to_list(result), expected)

        # Test case 2
        head = self.list_to_linkedlist([1])
        n = 1
        expected = []
        result = solution.removeNthFromEnd(head, n)
        self.assertEqual(self.linkedlist_to_list(result), expected)

        # Test case 3
        head = self.list_to_linkedlist([1, 2])
        n = 1
        expected = [1]
        result = solution.removeNthFromEnd(head, n)
        self.assertEqual(self.linkedlist_to_list(result), expected)

if __name__ == "__main__":
    unittest.main()