import threading
from collections import deque
from typing import Callable

class FizzBuzz:
    def __init__(self, n: int):
        self.n = n
        self.arr = deque([val for val in range(1, n + 1)])
        self.cond = threading.Condition()

    # printFizz() outputs "fizz"
    def fizz(self, printFizz: 'Callable[[], None]') -> None:
    	while self.arr:
            with self.cond:
                while self.arr and (self.arr[0] % 3 != 0 or self.arr[0] % 15 == 0):
                    self.cond.wait()
                if self.arr:
                    printFizz()
                    self.arr.popleft()
                    self.cond.notify_all()
                else:
                    self.cond.notify_all()
                    return

    # printBuzz() outputs "buzz"
    def buzz(self, printBuzz: 'Callable[[], None]') -> None:
    	while self.arr:
            with self.cond:
                while self.arr and (self.arr[0] % 5 != 0 or self.arr[0] % 15 == 0):
                    self.cond.wait()
                if self.arr:
                    printBuzz()
                    self.arr.popleft()
                    self.cond.notify_all()
                else:
                    self.cond.notify_all()
                    return

    # printFizzBuzz() outputs "fizzbuzz"
    def fizzbuzz(self, printFizzBuzz: 'Callable[[], None]') -> None:
        while self.arr:
            with self.cond:
                while self.arr and self.arr[0] % 15 != 0:
                    self.cond.wait()
                if self.arr:
                    printFizzBuzz()
                    self.arr.popleft()
                    self.cond.notify_all()
                else:
                    self.cond.notify_all()
                    return

    # printNumber(x) outputs "x", where x is an integer.
    def number(self, printNumber: 'Callable[[int], None]') -> None:
        while self.arr:
            with self.cond:
                while self.arr and (self.arr[0] % 3 == 0 or self.arr[0] % 5 == 0):
                    self.cond.wait()
                if self.arr:
                    printNumber(self.arr.popleft())
                    self.cond.notify_all()
                else:
                    self.cond.notify_all()
                    return