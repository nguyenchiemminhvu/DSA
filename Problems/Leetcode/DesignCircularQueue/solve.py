from typing import List
import unittest

class MyCircularQueue:
    INF = -1

    def __init__(self, k: int):
        self.arr = [MyCircularQueue.INF] * k
        self.cap = k
        self.size = 0
        self.head = -1
        self.tail = -1

    def enQueue(self, value: int) -> bool:
        if self.isFull():
            return False
        if self.isEmpty():
            self.head = 0
        self.tail = (self.tail + 1) % self.cap
        self.arr[self.tail] = value
        self.size += 1
        return True

    def deQueue(self) -> bool:
        if self.isEmpty():
            return False
        self.arr[self.head] = MyCircularQueue.INF
        if self.size == 1:
            self.head = self.tail = -1
        else:
            self.head = (self.head + 1) % self.cap
        self.size -= 1
        return True

    def Front(self) -> int:
        return self.arr[self.head]

    def Rear(self) -> int:
        return self.arr[self.tail]

    def isEmpty(self) -> bool:
        return self.size == 0

    def isFull(self) -> bool:
        return self.size == self.cap


# Your MyCircularQueue object will be instantiated and called as such:
# obj = MyCircularQueue(k)
# param_1 = obj.enQueue(value)
# param_2 = obj.deQueue()
# param_3 = obj.Front()
# param_4 = obj.Rear()
# param_5 = obj.isEmpty()
# param_6 = obj.isFull()

class TestDesignCircularQueue(unittest.TestCase):
    def test_example1(self):
        circularQueue = MyCircularQueue(3)  # set the size to be 3
        self.assertTrue(circularQueue.enQueue(1))  # return true
        self.assertTrue(circularQueue.enQueue(2))  # return true
        self.assertTrue(circularQueue.enQueue(3))  # return true
        self.assertFalse(circularQueue.enQueue(4))  # return false, the queue is full
        self.assertEqual(circularQueue.Rear(), 3)  # return 3
        self.assertTrue(circularQueue.isFull())  # return true
        self.assertTrue(circularQueue.deQueue())  # return true
        self.assertTrue(circularQueue.enQueue(4))  # return true
        self.assertEqual(circularQueue.Rear(), 4)  # return 4

    def test_example2(self):
        circularQueue = MyCircularQueue(6)  # set the size to be 6
        self.assertTrue(circularQueue.enQueue(6))  # return true
        self.assertEqual(circularQueue.Rear(), 6)  # return 6
        self.assertTrue(circularQueue.deQueue())  # return true
        self.assertTrue(circularQueue.enQueue(5))  # return true
        self.assertEqual(circularQueue.Rear(), 5)  # return 5
        self.assertTrue(circularQueue.deQueue())  # return true
        self.assertEqual(circularQueue.Front(), -1)  # return -1, the queue is empty
        self.assertFalse(circularQueue.deQueue())  # return false, the queue is empty
        self.assertFalse(circularQueue.deQueue())  # return false, the queue is empty
        self.assertTrue(circularQueue.enQueue(3))  # return true
        self.assertEqual(circularQueue.Rear(), 3)  # return 3
        self.assertEqual(circularQueue.Front(), 3)  # return 3

if __name__ == "__main__":
    unittest.main()