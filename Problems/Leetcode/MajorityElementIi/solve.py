class Solution:
    def majorityElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        k = n // 3
        nums.sort()
        res = set()
        i = 0
        while i < n:
            if i + k < n and nums[i] == nums[i + k]:
                res.add(nums[i])
                i += k
            i += 1
        return list(res)