from typing import List

class Solution:
    def findXSum(self, nums: List[int], k: int, x: int) -> List[int]:
        def xsum(arr: List[int]) -> int:
            freq = {}
            for val in arr:
                freq[val] = freq.get(val, 0) + 1
            arr.sort(key=lambda x: (-freq[x], -x))
            
            count_diff = 0
            prev = -1
            s = 0
            for val in arr:
                if val != prev:
                    count_diff += 1
                    if count_diff > x:
                        break
                s += val
                prev = val
            return s

        n = len(nums)
        res = []
        for i in range(k, n + 1):
            sub = nums[i-k:i]
            res.append(xsum(sub))
        return res