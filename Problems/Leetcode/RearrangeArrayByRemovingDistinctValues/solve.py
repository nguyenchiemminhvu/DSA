from collections import Counter

class Solution:
    def rearrangeArray(self, nums: list[int]) -> list[int]:
        count = Counter(nums)
        keys = sorted(count)
        
        res = []

        for _ in range(max(count.values())):
            for k in keys:
                if count[k] > 0:
                    res.append(k)
                    count[k] -= 1

        return res