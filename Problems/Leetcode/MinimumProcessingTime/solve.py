from typing import List

class Solution:
    def minProcessingTime(self, cpu_time: List[int], tasks: List[int]) -> int:
        cpu_time.sort()
        tasks.sort(key=lambda x: -x)

        res = 0
        it = 0
        ic = 0
        while ic < len(cpu_time):
            res = max(res, cpu_time[ic] + tasks[it])
            ic += 1
            it += 4

        return res