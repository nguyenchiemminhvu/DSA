from typing import List
import heapq

class NumberContainers:

    def __init__(self):
        self.map_idx = {} # index -> value
        self.map_val = {} # value -> [index]

    def change(self, index: int, number: int) -> None:
        if number not in self.map_val:
            self.map_idx[index] = number
            self.map_val[number] = [index]
        else:
            self.map_idx[index] = number
            heapq.heappush(self.map_val[number], index)

    def find(self, number: int) -> int:
        if number not in self.map_val:
            return -1
        while self.map_val[number] and self.map_val[number][0] in self.map_idx and number != self.map_idx[self.map_val[number][0]]:
            heapq.heappop(self.map_val[number])
        if self.map_val[number]:
            return self.map_val[number][0]
        return -1

# Your NumberContainers object will be instantiated and called as such:
# obj = NumberContainers()
# obj.change(index,number)
# param_2 = obj.find(number)