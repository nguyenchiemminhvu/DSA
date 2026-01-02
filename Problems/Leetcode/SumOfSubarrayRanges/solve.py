class Solution:
    def subArrayRanges(self, nums: List[int]) -> int:
        # n = len(nums)
        # res = 0
        # for i in range(n):
        #     for j in range(i + 1, n):
        #         res += max(nums[i:j+1]) - min(nums[i:j+1])
        # return res

        n = len(nums)
        res = 0

        min_left = [-1] * n
        min_right = [n] * n
        max_left = [-1] * n
        max_right = [n] * n

        # left to right - find min_left and max_left using 2 monotonic stacks
        st_min = []
        st_max = []
        for i in range(n):
            while st_min and nums[st_min[-1]] >= nums[i]:
                st_min.pop()
            if st_min:
                min_left[i] = st_min[-1]
            st_min.append(i)

            while st_max and nums[st_max[-1]] <= nums[i]:
                st_max.pop()
            if st_max:
                max_left[i] = st_max[-1]
            st_max.append(i)
        
        # right to left - find min_right and max_right using 2 monotonic stacks
        st_min = []
        st_max = []
        for i in range(n - 1, -1, -1):
            while st_min and nums[st_min[-1]] > nums[i]:
                st_min.pop()
            if st_min:
                min_right[i] = st_min[-1]
            st_min.append(i)

            while st_max and nums[st_max[-1]] < nums[i]:
                st_max.pop()
            if st_max:
                max_right[i] = st_max[-1]
            st_max.append(i)

        for i in range(n):
            res += nums[i] * (i - max_left[i]) * (max_right[i] - i)
            res -= nums[i] * (i - min_left[i]) * (min_right[i] - i)

        return res