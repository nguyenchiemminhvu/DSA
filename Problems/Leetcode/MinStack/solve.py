from typing import List
import unittest

class MinStack:

    def __init__(self):
        self.arr = []

    def push(self, val: int) -> None:
        if len(self.arr) > 0:
            cur_min = self.arr[-1][1]
            self.arr.append((val, min(cur_min, val)))
        else:
            self.arr.append((val, val))

    def pop(self) -> None:
        if len(self.arr) > 0:
            self.arr.pop()

    def top(self) -> int:
        return self.arr[-1][0]

    def getMin(self) -> int:
        return self.arr[-1][1]


# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(val)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()

class TestMinStack(unittest.TestCase):

    def test_case_1(self):
        min_stack = MinStack()
        min_stack.push(-2)
        min_stack.push(0)
        min_stack.push(-3)
        self.assertEqual(min_stack.getMin(), -3)
        min_stack.pop()
        self.assertEqual(min_stack.top(), 0)
        self.assertEqual(min_stack.getMin(), -2)

    def test_case_2(self):
        min_stack = MinStack()
        min_stack.push(1)
        min_stack.push(2)
        self.assertEqual(min_stack.top(), 2)
        self.assertEqual(min_stack.getMin(), 1)

    def test_case_3(self):
        min_stack = MinStack()
        min_stack.push(0)
        min_stack.push(1)
        min_stack.push(0)
        self.assertEqual(min_stack.getMin(), 0)
        min_stack.pop()
        self.assertEqual(min_stack.getMin(), 0)

if __name__ == "__main__":
    unittest.main()