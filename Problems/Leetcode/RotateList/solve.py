from typing import Optional
import unittest

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def rotateRight(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        if head == None or head.next == None:
            return head

        n = 0
        cur = head
        while cur:
            n += 1
            cur = cur.next
        
        k %= n
        if k == 0:
            return head

        dummy = ListNode(0)
        dummy.next = head

        slow = dummy
        fast = dummy
        while k > 0:
            k -= 1
            fast = fast.next
        
        while fast and fast.next:
            slow = slow.next
            fast = fast.next
        
        new_head = slow.next
        slow.next = None
        fast.next = head
        return new_head

class TestRotateList(unittest.TestCase):
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

    def test_rotateRight(self):
        sol = Solution()

        head = self.list_to_linkedlist([1,2,3,4,5])
        k = 2
        result = sol.rotateRight(head, k)
        self.assertEqual(self.linkedlist_to_list(result), [4,5,1,2,3])

        head = self.list_to_linkedlist([0,1,2])
        k = 4
        result = sol.rotateRight(head, k)
        self.assertEqual(self.linkedlist_to_list(result), [2,0,1])

        head = self.list_to_linkedlist([])
        k = 0
        result = sol.rotateRight(head, k)
        self.assertEqual(self.linkedlist_to_list(result), [])

        head = self.list_to_linkedlist([1])
        k = 99
        result = sol.rotateRight(head, k)
        self.assertEqual(self.linkedlist_to_list(result), [1])

if __name__ == "__main__":
    unittest.main()