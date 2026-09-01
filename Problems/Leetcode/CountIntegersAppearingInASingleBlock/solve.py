from collections import defaultdict

class Solution:
    def countSpecialIntegers(self, nums: list[int]) -> int:
        m = defaultdict(list)
        for i, val in enumerate(nums):
            if val not in m:
                m[val] = [i]
            elif nums[i] == nums[i - 1]:
                m[val][-1] = i
            else:
                m[val].append(i)

        return sum(1 for val in m if len(m[val]) == 1)