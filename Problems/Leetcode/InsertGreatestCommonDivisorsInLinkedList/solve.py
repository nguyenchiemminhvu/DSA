from typing import Optional
import math
import unittest

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def insertGreatestCommonDivisors(self, head: Optional[ListNode]) -> Optional[ListNode]:
        current = head
        while current != None and current.next != None:
            g = math.gcd(current.val, current.next.val)
            n = ListNode(val=g)
            n.next = current.next
            current.next = n
            current = n.next
        return head

class TestInsertGreatestCommonDivisorsInLinkedList(unittest.TestCase):
    def list_to_linkedlist(self, lst):
        if not lst:
            return None
        head = ListNode(lst[0])
        current = head
        for value in lst[1:]:
            current.next = ListNode(value)
            current = current.next
        return head

    def linkedlist_to_list(self, head):
        lst = []
        current = head
        while current:
            lst.append(current.val)
            current = current.next
        return lst

    def test_example1(self):
        sol = Solution()
        head = self.list_to_linkedlist([12, 15, 18])
        expected = [12, 3, 15, 3, 18]
        result_head = sol.insertGreatestCommonDivisors(head)
        result = self.linkedlist_to_list(result_head)
        self.assertEqual(result, expected)

    def test_example2(self):
        sol = Solution()
        head = self.list_to_linkedlist([7])
        expected = [7]
        result_head = sol.insertGreatestCommonDivisors(head)
        result = self.linkedlist_to_list(result_head)
        self.assertEqual(result, expected)

    def test_empty_list(self):
        sol = Solution()
        head = self.list_to_linkedlist([])
        expected = []
        result_head = sol.insertGreatestCommonDivisors(head)
        result = self.linkedlist_to_list(result_head)
        self.assertEqual(result, expected)

    def test_single_node(self):
        sol = Solution()
        head = self.list_to_linkedlist([5])
        expected = [5]
        result_head = sol.insertGreatestCommonDivisors(head)
        result = self.linkedlist_to_list(result_head)
        self.assertEqual(result, expected)

    def test_two_nodes(self):
        sol = Solution()
        head = self.list_to_linkedlist([8, 12])
        expected = [8, 4, 12]
        result_head = sol.insertGreatestCommonDivisors(head)
        result = self.linkedlist_to_list(result_head)
        self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()