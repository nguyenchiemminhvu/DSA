class StockSpanner:

    def __init__(self):
        self.arr = []
        self.st = []

    def next(self, price: int) -> int:
        span = 1
        self.arr.append(price)
        while self.st and self.arr[self.st[-1]] <= price:
            self.st.pop()
        if self.st:
            span = max(span, len(self.arr) - self.st[-1] - 1)
        else:
            span = len(self.arr)
        self.st.append(len(self.arr) - 1)
        return span


# Your StockSpanner object will be instantiated and called as such:
# obj = StockSpanner()
# param_1 = obj.next(price)