from typing import Optional
import unittest

# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random

class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':       
        if head == None:
            return head

        index = 0
        cur = head
        new_arr = []

        while cur:
            new_arr.append(Node(cur.val))
            cur.val = index
            index += 1
            cur = cur.next
        
        for i in range(1, len(new_arr)):
            new_arr[i - 1].next = new_arr[i]

        cur = head
        while cur:
            if cur.random:
                from_index = cur.val
                to_index = cur.random.val
                new_arr[from_index].random = new_arr[to_index]
            cur = cur.next
        
        return new_arr[0]

class TestCopyListWithRandomPointer(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def list_to_nodes(self, lst):
        if not lst:
            return None
        nodes = [Node(x[0]) for x in lst]
        for i, (val, rand_idx) in enumerate(lst):
            if i < len(nodes) - 1:
                nodes[i].next = nodes[i + 1]
            if rand_idx is not None:
                nodes[i].random = nodes[rand_idx]
        return nodes[0]

    def nodes_to_list(self, head):
        result = []
        node_map = {}
        cur = head
        index = 0
        while cur:
            node_map[cur] = index
            result.append([cur.val, None])
            cur = cur.next
            index += 1
        cur = head
        index = 0
        while cur:
            if cur.random:
                result[index][1] = node_map[cur.random]
            cur = cur.next
            index += 1
        return result

    def test_example1(self):
        head = self.list_to_nodes([[7, None], [13, 0], [11, 4], [10, 2], [1, 0]])
        copied_head = self.solution.copyRandomList(head)
        self.assertEqual(self.nodes_to_list(copied_head), [[7, None], [13, 0], [11, 4], [10, 2], [1, 0]])

    def test_example2(self):
        head = self.list_to_nodes([[1, 1], [2, 1]])
        copied_head = self.solution.copyRandomList(head)
        self.assertEqual(self.nodes_to_list(copied_head), [[1, 1], [2, 1]])

    def test_example3(self):
        head = self.list_to_nodes([[3, None], [3, 0], [3, None]])
        copied_head = self.solution.copyRandomList(head)
        self.assertEqual(self.nodes_to_list(copied_head), [[3, None], [3, 0], [3, None]])

    def test_empty_list(self):
        head = self.list_to_nodes([])
        copied_head = self.solution.copyRandomList(head)
        self.assertEqual(self.nodes_to_list(copied_head), [])

    def test_single_node_no_random(self):
        head = self.list_to_nodes([[1, None]])
        copied_head = self.solution.copyRandomList(head)
        self.assertEqual(self.nodes_to_list(copied_head), [[1, None]])

if __name__ == "__main__":
    unittest.main()