from typing import List

class Solution:
    def asteroidsDestroyed(self, mass: int, other_masses: List[int]) -> bool:
        other_masses.sort()
        for val in other_masses:
            if mass >= val:
                mass += val
            else:
                return False
        return True