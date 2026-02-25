from typing import List

class Solution:
    def maxCount(self, banned: List[int], n: int, limit: int) -> int:
        s = set(banned)
        cur_sum = 0
        count = 0
        for i in range(1, n + 1):
            if i not in s and cur_sum + i <= limit:
                cur_sum += i
                count += 1
        return count