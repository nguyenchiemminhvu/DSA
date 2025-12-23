from typing import List
from itertools import permutations

class Solution:
    def maxCompatibilitySum(self, students: List[List[int]], mentors: List[List[int]]) -> int:
        res = 0
        n = len(students)
        perms = permutations([i for i in range(n)])
        for m_idx in perms:
            count = 0
            i = 0
            for im in m_idx:
                # map result of students[i] with mentors[im]
                count += sum(1 if students[i][j] == mentors[im][j] else 0 for j in range(len(students[i])))
                i += 1
            res = max(res, count)
        return res