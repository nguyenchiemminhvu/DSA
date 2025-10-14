from typing import List

class Solution:
    def findArray(self, pref: List[int]) -> List[int]:
        cur_xor = pref[0]
        arr = [pref[0]]
        for i in range(1, len(pref)):
            arr.append(cur_xor ^ pref[i])
            cur_xor ^= arr[-1]
        return arr