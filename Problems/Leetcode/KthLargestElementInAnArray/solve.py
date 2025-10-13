import heapq

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        arr = []
        for val in nums:
            heapq.heappush(arr, val)
            while len(arr) > k:
                heapq.heappop(arr)
        return arr[0]