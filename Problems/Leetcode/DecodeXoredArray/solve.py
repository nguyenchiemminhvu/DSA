from typing import List

class Solution:
    def decode(self, encoded: List[int], first: int) -> List[int]:
        arr = [first]
        for val in encoded:
            arr.append(arr[-1] ^ val)
        return arr