from typing import List
import heapq

class max_heap:
    def __init__(self):
        self.pq = []
    def __bool__(self):
        return True if self.pq else False
    def push(self, val:int):
        heapq.heappush(self.pq, -val)
    def pop(self):
        if not self.pq:
            return None
        return -heapq.heappop(self.pq)

class Solution:
    def maxKelements(self, nums: List[int], k: int) -> int:
        heap = max_heap()
        for val in nums:
            heap.push(val)
        
        res = 0
        while heap and k:
            score = heap.pop()
            res += score
            heap.push((score + 2) // 3)
            k -= 1
        return res