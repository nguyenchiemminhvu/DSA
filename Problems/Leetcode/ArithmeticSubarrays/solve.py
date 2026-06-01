from typing import List

class Solution:
    def checkArithmeticSubarrays(self, nums: List[int], l_query: List[int], r_query: List[int]) -> List[bool]:
        def check(arr: List[int], n: int) -> bool:
            mn, ma = min(arr), max(arr)
            if (ma - mn) % (n - 1) != 0:
                return False
            
            d = (ma - mn) // (n - 1)
            if d == 0:
                return all(val == mn for val in arr)
            
            seen = [False] * n
            for val in arr:
                sub_d = val - mn
                if sub_d % d != 0:
                    return False
                idx = sub_d // d
                if idx < 0 or idx >= n or seen[idx]:
                    return False
                seen[idx] = True
            return all(seen)

        res = []
        m = len(l_query)
        for i in range(m):
            l, r = l_query[i], r_query[i]
            res.append(check(nums[l: r + 1], r - l + 1))
        return res