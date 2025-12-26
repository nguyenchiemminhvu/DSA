from typing import List

class Solution:
    def maxChunksToSorted(self, arr: List[int]) -> int:
        cur_min = 0
        found_cur_min = False
        cur_max = 0
        s = set()
        count = 0
        i = 0
        while i < len(arr):
            s.add(arr[i])
            if arr[i] == cur_min:
                found_cur_min = True
            cur_max = max(cur_max, arr[i])
            if found_cur_min and all(val in s for val in range(cur_min, cur_max + 1)):
                cur_min = cur_max + 1
                cur_max = cur_min
                count += 1
                found_cur_min = False
            i += 1
        return count