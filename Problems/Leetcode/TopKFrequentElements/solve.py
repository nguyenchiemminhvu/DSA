import heapq
from typing import List
import unittest

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        freq = {}
        for val in nums:
            freq[val] = freq.get(val, 0) + 1
        
        heap = []
        for f, v in freq.items():
            heapq.heappush(heap, (v, f))
            while len(heap) > k:
                heapq.heappop(heap)
        return [tup[1] for tup in heap]

class TestTopKFrequentElements(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [1,1,1,2,2,3]
        k = 2
        expected = [1, 2]
        result = self.solution.topKFrequent(nums, k)
        self.assertCountEqual(result, expected)

    def test_example2(self):
        nums = [1]
        k = 1
        expected = [1]
        result = self.solution.topKFrequent(nums, k)
        self.assertCountEqual(result, expected)

    def test_single_element_multiple_times(self):
        nums = [4,4,4,4]
        k = 1
        expected = [4]
        result = self.solution.topKFrequent(nums, k)
        self.assertCountEqual(result, expected)

if __name__ == "__main__":
    unittest.main()
