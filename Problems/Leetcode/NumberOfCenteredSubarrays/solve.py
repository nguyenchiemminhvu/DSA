from typing import List

class Solution:
    def centeredSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        res = 0

        map_pos = {}
        for i, val in enumerate(nums):
            if val not in map_pos:
                map_pos[val] = []
            map_pos[val].append(i)

        prefix_sum = [0] * (n + 1)
        for i, val in enumerate(nums):
                prefix_sum[i + 1] = prefix_sum[i] + val

        for i in range(n):
            for j in range(i, n):
                # get sum subarray i..j
                sub_sum = prefix_sum[j + 1] - prefix_sum[i]
                
                # now, count how many values equal to sub_sum from i to j
                if sub_sum in map_pos:
                    for pos in map_pos[sub_sum]:
                        if pos >= i and pos <= j:
                            res += 1
                            break

        return res