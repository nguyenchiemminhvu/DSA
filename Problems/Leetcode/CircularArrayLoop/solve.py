from typing import List

class Solution:
    def circularArrayLoop(self, nums: List[int]) -> bool:
        n = len(nums)

        def next_idx(i: int) -> int:
            return ((i + nums[i]) + n) % n
        
        for i in range(n):
            slow = i
            fast = next_idx(i)

            while nums[slow] * nums[fast] > 0 and nums[slow] * nums[next_idx(fast)] > 0:
                if slow == fast:
                    if slow != next_idx(slow):
                        return True
                    break
                slow = next_idx(slow)
                fast = next_idx(next_idx(fast))
        
        return False