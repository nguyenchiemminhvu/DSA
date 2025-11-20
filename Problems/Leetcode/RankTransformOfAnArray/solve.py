from typing import List

class Solution:
    def arrayRankTransform(self, arr: List[int]) -> List[int]:
        fr = { val: i + 1 for i, val in enumerate(sorted(set(arr))) }
        return [fr[val] for val in arr]