from typing import List

class Solution:
    def sortTheStudents(self, score: List[List[int]], k: int) -> List[List[int]]:
        m, n = len(score), len(score[0])
        student_ids = [i for i in range(m)]
        student_ids.sort(key=lambda s: (score[s][k], s), reverse=True)

        res = []
        for sid in student_ids:
            res.append(score[sid])
        return res