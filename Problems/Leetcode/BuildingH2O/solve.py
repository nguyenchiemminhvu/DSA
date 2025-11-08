import threading
from typing import Callable

class H2O:
    def __init__(self):
        self.h_sem = threading.Semaphore(2)
        self.o_sem = threading.Semaphore(0)
        self.lock_count = threading.Lock()
        self.h_count = 0

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.h_sem.acquire()
        # releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen()
        self.lock_count.acquire()
        self.h_count += 1
        if self.h_count % 2 == 0:
            self.o_sem.release()
        self.lock_count.release()

    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.o_sem.acquire()
        # releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen()
        self.h_sem.release()
        self.h_sem.release()