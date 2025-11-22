from typing import List

class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        n = len(fruits)
        used = [False] * n
        count = 0
        for fruit in fruits:
            for i in range(n):
                if not used[i] and fruit <= baskets[i]:
                    used[i] = True
                    break
            else:
                count += 1
        return count