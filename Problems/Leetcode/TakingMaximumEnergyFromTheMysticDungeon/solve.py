from typing import List

class Solution:
    def maximumEnergy(self, energy: List[int], k: int) -> int:
        n = len(energy)
        for i in range(n - k - 1, -1, -1):
            energy[i] += energy[i + k]
        
        return max(energy)