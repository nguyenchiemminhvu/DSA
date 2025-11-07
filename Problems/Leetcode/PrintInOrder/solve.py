import threading

b1 = threading.Barrier(1)
b2 = threading.Barrier(2)
b3 = threading.Barrier(3)

class Foo:
    def __init__(self):
        pass


    def first(self, printFirst: 'Callable[[], None]') -> None:
        b1.wait()
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        b2.wait()
        b3.wait()


    def second(self, printSecond: 'Callable[[], None]') -> None:
        b2.wait()
        # printSecond() outputs "second". Do not change or remove this line.
        printSecond()
        b3.wait()


    def third(self, printThird: 'Callable[[], None]') -> None:
        b3.wait()
        # printThird() outputs "third". Do not change or remove this line.
        printThird()