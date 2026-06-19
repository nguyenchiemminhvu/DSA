from typing import List
import heapq

class MedianFinder:

    def __init__(self):
        self.left = [] # max heap
        self.right = [] # min heap

    def addNum(self, num: int) -> None:
        if not self.left:
            heapq.heappush(self.left, -num)
        else:
            if num <= -self.left[0]:
                heapq.heappush(self.left, -num)
            else:
                heapq.heappush(self.right, num)
        
        self.__balancing()
    
    def __balancing(self):
        while len(self.right) > len(self.left):
            heapq.heappush(self.left, -heapq.heappop(self.right))
        
        while len(self.left) > len(self.right) + 1:
            heapq.heappush(self.right, -heapq.heappop(self.left))

    def findMedian(self) -> float:
        if not self.left:
            return 0.0
        
        if len(self.left) == len(self.right):
            return (-self.left[0] + self.right[0]) / 2.0
        
        return -self.left[0]

# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()