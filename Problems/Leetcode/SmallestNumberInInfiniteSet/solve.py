import heapq

class SmallestInfiniteSet:

    def __init__(self):
        self.s = set([val for val in range(1, 1001)])
        self.pq = [val for val in range(1, 1001)]

    def popSmallest(self) -> int:
        val = heapq.heappop(self.pq)
        self.s.remove(val)
        return val

    def addBack(self, val: int) -> None:
        if val not in self.s:
            self.s.add(val)
            heapq.heappush(self.pq, val)


# Your SmallestInfiniteSet object will be instantiated and called as such:
# obj = SmallestInfiniteSet()
# param_1 = obj.popSmallest()
# obj.addBack(num)