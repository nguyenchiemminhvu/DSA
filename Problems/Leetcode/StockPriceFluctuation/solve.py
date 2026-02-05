import heapq

class StockPrice:

    def __init__(self):
        self.latest_time = 0
        self.min_heap = []
        self.max_heap = []
        self.real_price = {} # timestamp -> price

    def update(self, timestamp: int, price: int) -> None:
        self.latest_time = max(self.latest_time, timestamp)
        self.real_price[timestamp] = price
        heapq.heappush(self.min_heap, (price, timestamp))
        heapq.heappush(self.max_heap, (-price, timestamp))

    def current(self) -> int:
        return self.real_price[self.latest_time]

    def maximum(self) -> int:
        while self.max_heap and -self.max_heap[0][0] != self.real_price[self.max_heap[0][1]]:
            heapq.heappop(self.max_heap)
        return -self.max_heap[0][0]

    def minimum(self) -> int:
        while self.min_heap and self.min_heap[0][0] != self.real_price[self.min_heap[0][1]]:
            heapq.heappop(self.min_heap)
        return self.min_heap[0][0]


# Your StockPrice object will be instantiated and called as such:
# obj = StockPrice()
# obj.update(timestamp,price)
# param_2 = obj.current()
# param_3 = obj.maximum()
# param_4 = obj.minimum()