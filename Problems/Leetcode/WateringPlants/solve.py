from typing import List

class Solution:
    def wateringPlants(self, plants: List[int], cap: int) -> int:
        n = len(plants)
        steps = 0
        cur_water = cap
        for i in range(n):
            if plants[i] <= cur_water:
                cur_water -= plants[i]
                steps += 1
            else:
                cur_water = cap - plants[i]
                steps += (i * 2) + 1
        return steps