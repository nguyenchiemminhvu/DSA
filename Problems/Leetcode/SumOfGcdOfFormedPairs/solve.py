class Solution:
    def gcdSum(self, nums: list[int]) -> int:
        n = len(nums)
        prefix = []
        cur_max = 0
        for val in nums:
            cur_max = max(cur_max, val)
            prefix.append(math.gcd(cur_max, val))
        
        prefix.sort(reverse=True)

        res = 0
        l, r = 0, n - 1
        while l < r:
            a, b = prefix[l], prefix[r]
            res += math.gcd(a, b)
            l += 1
            r -= 1
        
        return res