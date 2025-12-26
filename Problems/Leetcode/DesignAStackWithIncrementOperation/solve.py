class CustomStack:

    def __init__(self, maxSize: int):
        self.st = []
        self.cap = maxSize

    def push(self, x: int) -> None:
        if len(self.st) < self.cap:
            self.st.append(x)

    def pop(self) -> int:
        if self.st:
            return self.st.pop()
        return -1

    def increment(self, k: int, val: int) -> None:
        for i in range(min(len(self.st), k)):
            self.st[i] += val

# Your CustomStack object will be instantiated and called as such:
# obj = CustomStack(maxSize)
# obj.push(x)
# param_2 = obj.pop()
# obj.increment(k,val)