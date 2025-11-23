from typing import List

class Solution:
    def maxSumDivThree(self, nums: List[int]) -> int:
        all_sum = sum(nums)
        remain = all_sum % 3
        if remain == 0:
            return all_sum
        
        remain_map = {}
        for val in nums:
            r = val % 3
            if r not in remain_map:
                remain_map[r] = []
            remain_map[r].append(val)
        
        if remain == 2:
            # remove smallest value that mod 3 == 2
            # or remove smallest couple values that mod 3 == 1
            opt1, opt2 = float('inf'), float('inf')
            if 1 in remain_map and len(remain_map[1]) > 1:
                rem_1_arr = sorted(remain_map[1])
                opt1 = (rem_1_arr[0] + rem_1_arr[1])
            if 2 in remain_map:
                opt2 = min(remain_map[2])
            all_sum -= min(opt1, opt2)
        else:
            # remove smallest value that mod 3 == 1
            # or remove smallest couple values that mode 3 == 2 ((2 + 2) % 3 == 1)
            opt1, opt2 = float('inf'), float('inf')
            if 1 in remain_map:
                opt1 = min(remain_map[1])
            if 2 in remain_map and len(remain_map[2]) > 1:
                rem_2_arr = sorted(remain_map[2])
                opt2 = (rem_2_arr[0] + rem_2_arr[1])
            all_sum -= min(opt1, opt2)
        
        return all_sum