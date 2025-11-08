from typing import List

class OrderedStream:
    def __init__(self, n: int):
        self.n = n
        self.arr = [""] * n
        self.idx = 0

    def insert(self, idKey: int, value: str) -> List[str]:
        self.arr[idKey - 1] = value
        i = self.idx
        res = []
        while i < self.n:
            if self.arr[i]:
                res.append(self.arr[i])
            else:
                self.idx = i
                break
            i += 1
        return res

# Your OrderedStream object will be instantiated and called as such:
# obj = OrderedStream(n)
# param_1 = obj.insert(idKey,value)