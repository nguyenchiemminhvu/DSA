# https://leetcode.com/problems/count-of-interesting-subarrays/

from collections import defaultdict
from typing import List

class Solution:
    def countInterestingSubarrays(self, nums: List[int], modulo: int, k: int) -> int:
        res = 0

        prefix_mod = 0
        freq = defaultdict(int)
        freq[0] = 1
        for n in nums:
            if n % modulo == k:
                prefix_mod += 1
            
            remainer = ((prefix_mod % modulo) + modulo) % modulo
            target_remainer = ((remainer - k) + modulo) % modulo
            res += freq[target_remainer]
            freq[remainer] += 1

        return res

if __name__ == "__main__":
    nums = [1, 2, 3, 4]
    modulo = 2
    k = 1
    solution = Solution()
    print(solution.countInterestingSubarrays(nums, modulo, k))