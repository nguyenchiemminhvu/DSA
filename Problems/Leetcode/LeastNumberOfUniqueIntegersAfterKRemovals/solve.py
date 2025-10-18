from typing import List

class Solution:
    def findLeastNumOfUniqueInts(self, arr: List[int], k: int) -> int:
        freq = {}
        for val in arr:
            freq[val] = freq.get(val, 0) + 1
        s = sorted(set(arr), key=lambda x: freq[x])
        for val in s:
            if k >= freq[val]:
                k -= freq[val]
                freq.pop(val)
            else:
                break
        return len(freq)