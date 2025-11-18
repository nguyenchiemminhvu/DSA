from typing import List

class Solution:
    def busyStudent(self, s: List[int], e: List[int], q: int) -> int:
        count = 0
        for i in range(len(s)):
            if s[i] <= q <= e[i]:
                count += 1
        return count