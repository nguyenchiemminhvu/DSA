from typing import Optional
import unittest

# Definition for a Node.
class Node:
    def __init__(self, val, prev, next, child):
        self.val = val
        self.prev = prev
        self.next = next
        self.child = child

class Solution:
    def flatten(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if head == None:
            return head
        
        if head.child:
            head_child = self.flatten(head.child)
            end_child = head_child
            while end_child and end_child.next:
                end_child.next.prev = end_child
                end_child = end_child.next
            end_child.next = head.next
            if head.next:
                head.next.prev = end_child
            head.next = head_child
            head_child.prev = head
            head.child = None
        else:
            head.next = self.flatten(head.next)
        return head

class TestFlattenAMultiLevelDoublyLinkedList(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def list_to_doubly_linked_list(self, lst):
        if not lst:
            return None
        head = Node(lst[0], None, None, None)
        current = head
        for val in lst[1:]:
            new_node = Node(val, current, None, None)
            current.next = new_node
            current = new_node
        return head

    def doubly_linked_list_to_list(self, head):
        result = []
        current = head
        while current:
            result.append(current.val)
            current = current.next
        return result

    def test_flatten(self):
        # Test case 1: Simple case with one level of children
        head = self.list_to_doubly_linked_list([1, 2, 3])
        head.child = self.list_to_doubly_linked_list([4, 5])
        flattened = self.solution.flatten(head)
        self.assertEqual(self.doubly_linked_list_to_list(flattened), [1, 4, 5, 2, 3])

        # Test case 2: More complex case with multiple levels of children
        head = self.list_to_doubly_linked_list([1, 2])
        head.child = self.list_to_doubly_linked_list([3])
        head.child.child = self.list_to_doubly_linked_list([4, 5])
        flattened = self.solution.flatten(head)
        self.assertEqual(self.doubly_linked_list_to_list(flattened), [1, 3, 4, 5, 2])

        # Test case 3: No children
        head = self.list_to_doubly_linked_list([1, 2, 3])
        flattened = self.solution.flatten(head)
        self.assertEqual(self.doubly_linked_list_to_list(flattened), [1, 2, 3])

        # Test case 4: Empty list
        head = None
        flattened = self.solution.flatten(head)
        self.assertIsNone(flattened)

if __name__ == '__main__':
    unittest.main()