from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> bool:
        def binary_search(nums: List[int], target: int, left: int, right: int) -> bool:
            if left > right:
                return False
            mid = left + (right - left) // 2
            if target == nums[mid]:
                return True
            if nums[right] <= nums[left]:
                found_left = binary_search(nums, target, left, mid - 1)
                if found_left:
                    return found_left
                else:
                    return binary_search(nums, target, mid + 1, right)
            else:
                if target == nums[mid]:
                    return True
                if target > nums[mid]:
                    return binary_search(nums, target, mid + 1, right)
                else:
                    return binary_search(nums, target, left, mid - 1)
            return False
        
        return binary_search(nums, target, 0, len(nums) - 1)