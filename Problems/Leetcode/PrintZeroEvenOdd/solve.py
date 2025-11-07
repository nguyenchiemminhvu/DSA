import threading
from collections import deque
from typing import Callable

class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.arr = deque([val for p in zip([0] * n, range(1, n + 1)) for val in p])
        self.idx = 0
        self.cond = threading.Condition()

    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        while self.arr:
            with self.cond:
                while self.arr and self.arr[0] != 0:
                    self.cond.wait()
                if self.arr:
                    printNumber(self.arr.popleft())
                    self.cond.notify_all()
                else:
                    self.cond.notify_all()
                    return
    
    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        while self.arr:
            with self.cond:
                while self.arr and self.arr[0] % 2 != 1:
                    self.cond.wait()
                if self.arr:
                    printNumber(self.arr.popleft())
                    self.cond.notify_all()
                else:
                    self.cond.notify_all()
                    return

    def even(self, printNumber: 'Callable[[int], None]') -> None:
        while self.arr:
            with self.cond:
                while self.arr and (self.arr[0] == 0 or self.arr[0] % 2 == 1):
                    self.cond.wait()
                if self.arr:
                    printNumber(self.arr.popleft())
                    self.cond.notify_all()
                else:
                    self.cond.notify_all()
                    return