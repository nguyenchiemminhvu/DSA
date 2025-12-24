class DataStream:

    def __init__(self, value: int, k: int):
        self.value = value
        self.k = k
        self.count_wrong = 0
        self.n = 0

    def consec(self, num: int) -> bool:
        self.n += 1
        if num != self.value:
            self.count_wrong = self.k
        else:
            self.count_wrong -= 1
            if self.count_wrong < 0:
                self.count_wrong = 0
        
        if self.n < self.k or self.count_wrong > 0:
            return False
        return True

# Your DataStream object will be instantiated and called as such:
# obj = DataStream(value, k)
# param_1 = obj.consec(num)