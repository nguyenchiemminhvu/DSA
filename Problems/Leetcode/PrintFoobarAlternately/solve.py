import threading
from typing import Callable

class FooBar:
    def __init__(self, n):
        self.n = n
        self.cond = threading.Condition()
        self.selected = 1

    def foo(self, printFoo: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.cond.acquire()
            while self.selected != 1:
                self.cond.wait()
            # printFoo() outputs "foo". Do not change or remove this line.
            printFoo()
            self.selected = 2
            self.cond.notify()
            self.cond.release()

    def bar(self, printBar: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.cond.acquire()
            while self.selected != 2:
                self.cond.wait()
            # printBar() outputs "bar". Do not change or remove this line.
            printBar()
            self.selected = 1
            self.cond.notify()
            self.cond.release()