from typing import List

class Solution:
    def averageWaitingTime(self, customers: List[List[int]]) -> float:
        wait_time = 0.0
        end_time = 0.0
        for arrive, duration in customers:
            end_time = max(end_time, arrive) + duration
            wait_time += end_time - arrive
        return wait_time / len(customers)