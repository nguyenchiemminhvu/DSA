from typing import Optional
import unittest

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def oddEvenList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head == None or head.next == None:
            return head
        
        back = head
        front = head.next
        even_head = front

        while front != None:
            back.next = front.next
            back = back.next
            back, front = front, back
        
        cur = head
        while cur.next != None:
            cur = cur.next
        cur.next = even_head

        return head

class TestOddEvenLinkedList(unittest.TestCase):
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

    def test_oddEvenList(self):
        sol = Solution()

        # Test case 1
        head = self.list_to_linkedlist([1, 2, 3, 4, 5])
        expected = [1, 3, 5, 2, 4]
        result = sol.oddEvenList(head)
        self.assertEqual(self.linkedlist_to_list(result), expected)

        # Test case 2
        head = self.list_to_linkedlist([2, 1, 3, 5, 6, 4, 7])
        expected = [2, 3, 6, 7, 1, 5, 4]
        result = sol.oddEvenList(head)
        self.assertEqual(self.linkedlist_to_list(result), expected)

        # Test case 3: Empty list
        head = self.list_to_linkedlist([])
        expected = []
        result = sol.oddEvenList(head)
        self.assertEqual(self.linkedlist_to_list(result), expected)

        # Test case 4: Single node
        head = self.list_to_linkedlist([1])
        expected = [1]
        result = sol.oddEvenList(head)
        self.assertEqual(self.linkedlist_to_list(result), expected)

        # Test case 5: Two nodes
        head = self.list_to_linkedlist([1, 2])
        expected = [1, 2]
        result = sol.oddEvenList(head)
        self.assertEqual(self.linkedlist_to_list(result), expected)

if __name__ == "__main__":
    unittest.main()