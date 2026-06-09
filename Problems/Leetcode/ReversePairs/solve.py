from typing import List

class Solution:
    def reversePairs(self, nums: List[int]) -> int:
        n = len(nums)

        # res = 0
        # for i in range(n):
        #     for j in range(i + 1, n):
        #         if nums[i] > nums[j] * 2:
        #             res += 1
        # return res

        def merge_count(l: int, r: int) -> int:
            if l >= r:
                return 0
            
            mid = l + (r - l) // 2
            res = merge_count(l, mid) + merge_count(mid + 1, r)

            j = mid + 1
            for i in range(l, mid + 1):
                while j <= r and nums[i] > 2 * nums[j]:
                    j += 1
                res += (j - mid - 1)
            
            temp = []
            i, j = l, mid + 1
            while i <= mid and j <= r:
                if nums[i] <= nums[j]:
                    temp.append(nums[i])
                    i += 1
                else:
                    temp.append(nums[j])
                    j += 1
            
            while i <= mid:
                temp.append(nums[i])
                i += 1
            
            while j <= r:
                temp.append(nums[j])
                j += 1

            nums[l:r + 1] = temp
            return res
        
        return merge_count(0, n - 1)