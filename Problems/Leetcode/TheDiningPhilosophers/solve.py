import threading
from typing import Callable

cond = threading.Condition()
idx = 0
n = 5

class DiningPhilosophers:

    # call the functions directly to execute, for example, eat()
    def wantsToEat(self,
                   philosopher: int,
                   pickLeftFork: 'Callable[[], None]',
                   pickRightFork: 'Callable[[], None]',
                   eat: 'Callable[[], None]',
                   putLeftFork: 'Callable[[], None]',
                   putRightFork: 'Callable[[], None]') -> None:
        global idx
        global n
        with cond:
            while philosopher != idx:
                cond.wait()
            pickLeftFork()
            pickRightFork()
            eat()
            putLeftFork()
            putRightFork()
            idx = (idx + 2) % n
            cond.notify_all()