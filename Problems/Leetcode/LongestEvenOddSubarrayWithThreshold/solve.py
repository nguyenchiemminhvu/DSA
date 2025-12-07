from typing import List

class Solution:
    def longestAlternatingSubarray(self, nums: List[int], threshold: int) -> int:
        def split_threshold(arr: List[int], threshold: int) -> List[List[int]]:
            arr.append(threshold + 1)
            arrs = []
            cur_arr = []
            for val in arr:
                if val <= threshold:
                    cur_arr.append(val)
                else:
                    arrs.append(cur_arr)
                    cur_arr = []
            arr.pop()
            return arrs
        
        res = 0
        arrs = split_threshold(nums, threshold)
        for arr in arrs:
            na = len(arr)
            for i in range(na):
                if arr[i] & 1:
                    continue
                
                sign = 1
                j = i + 1
                while j < na and (arr[j] & 1) == sign:
                    j += 1
                    sign = (sign + 1) % 2
                res = max(res, j - i)
        
        return res