from typing import List

class Stack:
    def __init__(self):
        self.st = []
        self.history = []
    def push(self, val:int) -> None:
        self.st.append(val)
        self.history.append("Push")
    def get(self) -> int:
        return self.arr[-1]
    def pop(self) -> None:
        self.st.pop()
        self.history.append("Pop")
    def get_history(self) -> List[str]:
        return self.history
    def __bool__(self):
        return True if self.arr else False

class Solution:
    def buildArray(self, target: List[int], n: int) -> List[str]:
        st = Stack()
        cur = 1
        for val in target:
            while cur < val:
                st.push(cur)
                st.pop()
                cur += 1
            st.push(cur)
            cur += 1
        return st.get_history()