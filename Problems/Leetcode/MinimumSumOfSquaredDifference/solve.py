from typing import List

class Solution:
    def minSumSquareDiff(self, nums1: List[int], nums2: List[int], k1: int, k2: int) -> int:
        n = len(nums1)
        k = k1 + k2
        diffs = [abs(val1 - val2) for val1, val2 in zip(nums1, nums2)]

        if k >= sum(diffs):
            return 0
        
        diffs.sort(reverse=True)

        i = 0
        cur_val = diffs[0]
        cur_count = 1
        while k > 0:
            j = i + 1
            while j < n and diffs[j] == cur_val:
                j += 1
                cur_count += 1
            
            next_val = diffs[j] if j < n else 0
            need = (cur_val - next_val) * cur_count

            if need <= k:
                k -= need
                cur_val = next_val
                if j < n:
                    i = j - 1
                else:
                    i = n - 1
            else:
                quo, rem = divmod(k, cur_count)
                cur_val -= quo

                res = (cur_count - rem) * (cur_val ** 2) + rem * ((cur_val - 1) ** 2)
                for d in diffs[cur_count:]:
                    res += d ** 2
                return res
        
        res = cur_count * (cur_val ** 2)
        for d in diffs[cur_count:]:
            res += d ** 2
        return res