from typing import List, Dict
import unittest

class Solution:
    def findRestaurant(self, list1: List[str], list2: List[str]) -> List[str]:
        m1 : Dict[str, int] = {}
        m2 : Dict[str, int] = {}
        for i, s in enumerate(list1):
            if s not in m1:
                m1[s] = i
        for i, s in enumerate(list2):
            if s not in m2:
                m2[s] = i

        min_sum = 0xFFFFFFFF
        res = []
        for s in list1:
            if s in m2:
                if m1[s] + m2[s] < min_sum:
                    min_sum = m1[s] + m2[s]
                    res = [s]
                elif m1[s] + m2[s] == min_sum:
                    res.append(s)
        return res

class TestMinimumIndexSumOfTwoLists(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        list1 = ["Shogun", "Tapioca Express", "Burger King", "KFC"]
        list2 = ["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
        expected = ["Shogun"]
        self.assertEqual(self.solution.findRestaurant(list1, list2), expected)

    def test_example2(self):
        list1 = ["Shogun", "Tapioca Express", "Burger King", "KFC"]
        list2 = ["KFC", "Shogun", "Burger King"]
        expected = ["Shogun"]
        self.assertEqual(self.solution.findRestaurant(list1, list2), expected)

if __name__ == "__main__":
    unittest.main()