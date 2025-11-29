from typing import List

class Solution:
    def sortEvenOdd(self, nums: List[int]) -> List[int]:
        n = len(nums)
        temp = [nums[i] for i in range(0, n, 2)]
        temp.sort()
        it = 0
        for i in range(0, n, 2):
            nums[i] = temp[it]
            it += 1
        
        temp = [nums[i] for i in range(1, n, 2)]
        temp.sort(reverse=True)
        it = 0
        for i in range(1, n, 2):
            nums[i] = temp[it]
            it += 1

        return numsz