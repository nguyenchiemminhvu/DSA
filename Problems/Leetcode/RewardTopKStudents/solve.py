from typing import List
from collections import defaultdict

class Solution:
    def topStudents(self, pos: List[str], neg: List[str], report: List[str], student_id: List[int], top: int) -> List[int]:
        spos = set(pos)
        sneg = set(neg)
        n = len(student_id)
        scores = defaultdict(int)
        for i in range(n):
            words = report[i].split()
            for word in words:
                if word in spos:
                    scores[student_id[i]] += 3
                elif word in sneg:
                    scores[student_id[i]] -= 1
                else:
                    scores[student_id[i]] += 0
        
        pq = [(v, -k) for k, v in scores.items()]
        heapq.heapify(pq)
        while len(pq) > top:
            heapq.heappop(pq)
        pq.sort(key=lambda x: (-x[0], -x[1]))
        return [-i for score, i in pq]