import heapq

class LUPrefix:

    def __init__(self, n: int):
        self.pq = []
        self.next = 1

    def upload(self, video: int) -> None:
        heapq.heappush(self.pq, video)
        while self.pq and self.pq[0] == self.next:
            self.next += 1
            heapq.heappop(self.pq)

    def longest(self) -> int:
        return self.next - 1

# Your LUPrefix object will be instantiated and called as such:
# obj = LUPrefix(n)
# obj.upload(video)
# param_2 = obj.longest()