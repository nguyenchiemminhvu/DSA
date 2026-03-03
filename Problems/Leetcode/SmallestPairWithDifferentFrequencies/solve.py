from collections import Counter

class Solution:
    def minDistinctFreqPair(self, nums: list[int]) -> list[int]:
        freq = Counter(nums)
        nums.sort()
        n = len(nums)
        for i in range(1, n):
            if freq[nums[i]] != freq[nums[0]]:
                return [nums[0], nums[i]]

        return [-1, -1]