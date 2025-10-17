from typing import List

class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        if sum(gas) < sum(cost):
            return -1
        n = len(gas)
        total_tank = 0
        cur_tank = 0
        selected = 0
        for i in range(n):
            total_tank += gas[i] - cost[i]
            cur_tank += gas[i] - cost[i]
            if cur_tank < 0:
                cur_tank = 0
                selected = i + 1
        return selected