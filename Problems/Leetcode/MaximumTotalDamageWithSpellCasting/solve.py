from typing import List, Dict
import unittest

class Solution:
    def maximumTotalDamage(self, power: List[int]) -> int:
        freq = {}
        for p in power:
            freq[p] = freq.get(p, 0) + 1
        
        n = len(freq)
        sorted_power = sorted(freq.keys())

        memo: Dict[int, int] = {}
        
        # F[i] = max(F[i - 1], power[i] * freq[power[i]] + F[j])
        # where power[j] < power[i] - 2
        def F(index: int) -> int:
            if index < 0:
                return 0
            
            if index in memo:
                return memo[index]
            
            dmg_skip_this = F(index - 1)

            cur_dmg = sorted_power[index] * freq[sorted_power[index]]
            prev_index = -1
            for j in range(index - 1, -1, -1):
                if sorted_power[j] < sorted_power[index] - 2:
                    prev_index = j
                    break
            dmg_take_this = cur_dmg + F(prev_index)

            memo[index] = max(dmg_skip_this, dmg_take_this)
            return memo[index]
        
        return F(n - 1)

class TestMaximumTotalDamageWithSpellCasting(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        power = [2, 2, 3, 3, 3, 4]
        expected = 9
        self.assertEqual(self.solution.maximumTotalDamage(power), expected)

    def test_example2(self):
        power = [1, 1, 1, 1]
        expected = 4
        self.assertEqual(self.solution.maximumTotalDamage(power), expected)

if __name__ == "__main__":
    unittest.main()