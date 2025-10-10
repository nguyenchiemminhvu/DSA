from typing import List, Tuple
import unittest

class Solution:
    def openLock(self, deadends: List[str], target: str) -> int:
        if "0000" in deadends:
            return -1
        if target == "0000":
            return 0
        
        target = tuple(map(lambda x: int(x), list(target)))
        start = tuple([0] * 4)

        def generate_candidates(arr: Tuple[int]) -> List[Tuple[int]]:
            candidates = []
            for i in range(0, 4):
                candidates.append(tuple(arr[j] if j != i else (((arr[j] - 1) + 10) % 10) for j in range(0, 4)))
                candidates.append(tuple(arr[j] if j != i else ((arr[j] + 1) % 10) for j in range(0, 4)))
            return candidates
        
        visited = set()
        disabled = set()
        for deadend in deadends:
            disabled.add(tuple(map(int, deadend)))
        
        Q = [start]
        visited.add(start)
        steps = 0
        while len(Q) > 0:
            cur_len = len(Q)
            while cur_len:
                cur_state = Q.pop(0)
                cur_len -= 1
                if cur_state == target:
                    return steps

                candidates = generate_candidates(cur_state)
                for candidate in candidates:
                    if candidate not in disabled and candidate not in visited:
                        visited.add(candidate)
                        Q.append(candidate)
            steps += 1

        return -1

class TestOpenTheLock(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        deadends = ["0201","0101","0102","1212","2002"]
        target = "0202"
        expected_output = 6
        self.assertEqual(self.solution.openLock(deadends, target), expected_output)

    def test_case_2(self):
        deadends = ["8888"]
        target = "0009"
        expected_output = 1
        self.assertEqual(self.solution.openLock(deadends, target), expected_output)

    def test_case_3(self):
        deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"]
        target = "8888"
        expected_output = -1
        self.assertEqual(self.solution.openLock(deadends, target), expected_output)

    def test_case_4(self):
        deadends = ["0000"]
        target = "8888"
        expected_output = -1
        self.assertEqual(self.solution.openLock(deadends, target), expected_output)

if __name__ == "__main__":
    unittest.main()