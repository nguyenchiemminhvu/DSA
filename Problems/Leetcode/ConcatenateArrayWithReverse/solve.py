class Solution:
    def concatWithReverse(self, nums: list[int]) -> list[int]:
        nums.extend(nums[::-1])
        return nums