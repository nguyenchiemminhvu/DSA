class Solution:
    def wiggleMaxLength(self, nums: List[int]) -> int:
        n = len(nums)
        memo = {} # 

        # F(i) is the longest wiggle subsequence length to index i-th
        def F(i:int, sign:int = -1) -> int:
            if i == n - 1:
                return 1
            
            if (i, sign) in memo:
                return memo[(i, sign)]

            max_len = 1
            for j in range(i + 1, n):
                if (nums[j] - nums[i]) * sign > 0:
                    max_len = max(max_len, 1 + F(j, sign * -1))
            
            memo[(i, sign)] = max_len
            return max_len
        
        return max(F(0, -1), F(0, 1))