import heapq
from typing import List

class Solution:
    def maxAverageRatio(self, classes: List[List[int]], extraStudents: int) -> float:
        def get_pass_ratio(p:int, t:int) -> float:
            return float(p) / float(t)
        
        def get_gain_ratio(p:int, t:int, extra:int) -> float:
            return get_pass_ratio(p + extra, t + extra) - get_pass_ratio(p, t)
        
        pq = []
        for c in classes:
            cur_pass, cur_total = c
            gain = get_gain_ratio(cur_pass, cur_total, 1)
            heapq.heappush(pq, (-gain, (cur_pass, cur_total)))

        while extraStudents > 0:
            class_with_bigest_gain = heapq.heappop(pq)
            cur_gain, (cur_pass, cur_total) = class_with_bigest_gain
            cur_pass += 1
            cur_total += 1
            new_gain = get_gain_ratio(cur_pass, cur_total, 1)
            heapq.heappush(pq, (-new_gain, (cur_pass, cur_total)))
            extraStudents -= 1
        
        sum_ratio = 0.0
        n = len(pq)
        while pq:
            cur_class = heapq.heappop(pq)
            cur_gain, (cur_pass, cur_total) = cur_class
            sum_ratio += (cur_pass / cur_total)

        return sum_ratio / n