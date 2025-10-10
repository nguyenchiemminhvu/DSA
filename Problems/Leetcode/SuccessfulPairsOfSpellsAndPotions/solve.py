from typing import List
import unittest

class Solution:
    def successfulPairs(self, spells: List[int], potions: List[int], success: int) -> List[int]:
        def lower_bound(arr: List[int], target: int) -> int:
            left, right = 0, len(arr) - 1
            found = right + 1
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] >= target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found
        
        res = []
        potions.sort()
        for spell in spells:
            remain = success / spell
            lower = lower_bound(potions, remain)
            res.append(len(potions) - lower)
        return res

class TestSuccessfulPairsOfSpellsAndPotions(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        spells = [5, 1, 3]
        potions = [1, 2, 3, 4, 5]
        success = 7
        expected = [4, 0, 3]
        self.assertEqual(self.solution.successfulPairs(spells, potions, success), expected)

    def test_example2(self):
        spells = [3, 1, 2]
        potions = [8, 5, 8]
        success = 16
        expected = [2, 0, 2]
        self.assertEqual(self.solution.successfulPairs(spells, potions, success), expected)

    def test_edge_case(self):
        spells = [1]
        potions = [1]
        success = 1
        expected = [1]
        self.assertEqual(self.solution.successfulPairs(spells, potions, success), expected)

if __name__ == "__main__":
    unittest.main()