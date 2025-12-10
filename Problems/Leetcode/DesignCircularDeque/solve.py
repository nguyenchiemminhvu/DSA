from typing import Optional

class ListNode:
    def __init__(self, val:int = 0):
        self.val = val
        self.next = None

class MyCircularDeque:

    def __init__(self, k: int):
        self.head = None
        self.tail = None
        self.cap = k
        self.size = 0

    def insertFront(self, value: int) -> bool:
        if self.size == self.cap:
            return False
        
        node = ListNode(value)
        node.next = self.head
        self.head = node
        if self.tail == None:
            self.tail = node
        self.size += 1
        return True

    def insertLast(self, value: int) -> bool:
        if self.size == self.cap:
            return False
        
        node = ListNode(value)
        if self.tail == None:
            self.head = self.tail = node
        else:
            self.tail.next = node
            self.tail = node
        self.size += 1
        return True

    def deleteFront(self) -> bool:
        if self.size == 0:
            return False
        
        self.head = self.head.next
        if self.head == None:
            self.tail = None
        self.size -= 1
        return True

    def deleteLast(self) -> bool:
        if self.size == 0:
            return False
        
        if self.head == self.tail:
            self.head = self.tail = None
        else:
            p = self.head
            while p.next != self.tail:
                p = p.next
            p.next = None
            self.tail = p
        self.size -= 1
        return True

    def getFront(self) -> int:
        if self.size == 0:
            return -1
        return self.head.val

    def getRear(self) -> int:
        if self.size == 0:
            return -1
        return self.tail.val

    def isEmpty(self) -> bool:
        return self.size == 0

    def isFull(self) -> bool:
        return self.size == self.cap


# Your MyCircularDeque object will be instantiated and called as such:
# obj = MyCircularDeque(k)
# param_1 = obj.insertFront(value)
# param_2 = obj.insertLast(value)
# param_3 = obj.deleteFront()
# param_4 = obj.deleteLast()
# param_5 = obj.getFront()
# param_6 = obj.getRear()
# param_7 = obj.isEmpty()
# param_8 = obj.isFull()