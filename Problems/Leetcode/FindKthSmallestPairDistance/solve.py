from typing import List

class Solution:
    def smallestDistancePair(self, nums: List[int], k: int) -> int:
        def count_pair_util(nums: List[int], dist_threshold:int) -> int:
            count = 0
            j = 0
            for i in range(len(nums)):
                while j < len(nums) and nums[j] - nums[i] <= dist_threshold:
                    j += 1
                count += (j - i - 1)
            return count
        
        nums.sort()
        min_dist = 0
        max_dist = max(nums) - min(nums)
        res = max_dist
        while min_dist <= max_dist:
            dist_threshold = min_dist + (max_dist - min_dist) // 2
            count_pairs_in_threshold = count_pair_util(nums, dist_threshold)
            if count_pairs_in_threshold >= k:
                res = dist_threshold
                max_dist = dist_threshold - 1
            else:
                min_dist = dist_threshold + 1
        return res