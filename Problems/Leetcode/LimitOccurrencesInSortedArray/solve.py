class Solution:
    def limitOccurrences(self, nums: list[int], k: int) -> list[int]:
        max_val = -1
        max_count = 0
        res = []
        for val in nums:
            if val > max_val:
                max_val = val
                max_count = 1
            else:
                max_count += 1
            
            if max_count <= k:
                res.append(val)
        return res