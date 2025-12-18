from typing import List

class Solution:
    def maximumEvenSplit(self, val: int) -> List[int]:
        if val & 1:
            return []
        
        s = 0
        cur = 2
        tmp = []
        while s + cur <= val:
            s += cur
            tmp.append(cur)
            cur += 2
        
        if s < val:
            remain = val - s
            if remain in tmp:
                tmp[-1] += remain
            else:
                tmp.append(remain)
        return tmp