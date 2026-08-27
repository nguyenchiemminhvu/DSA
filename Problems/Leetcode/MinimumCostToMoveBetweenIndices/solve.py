class Solution:
    def minCost(self, nums: list[int], queries: list[list[int]]) -> list[int]:
        n = len(nums)

        # left[i]  = cost to move i -> i-1
        # right[i] = cost to move i -> i+1
        left = [0] * n
        right = [0] * n

        for i in range(n):
            if i > 0:
                left[i] = nums[i] - nums[i - 1]

            if i < n - 1:
                right[i] = nums[i + 1] - nums[i]

        # Determine closest(i)
        for i in range(n):
            if i == 0:
                right[i] = 1

            elif i == n - 1:
                left[i] = 1

            else:
                left_diff = nums[i] - nums[i - 1]
                right_diff = nums[i + 1] - nums[i]

                if left_diff <= right_diff:
                    left[i] = 1
                else:
                    right[i] = 1

        # Prefix sums
        prefix_right = [0] * n
        prefix_left = [0] * n

        for i in range(1, n):
            prefix_right[i] = prefix_right[i - 1] + right[i - 1]
            prefix_left[i] = prefix_left[i - 1] + left[i]

        ans = []

        for l, r in queries:
            if l < r:
                ans.append(prefix_right[r] - prefix_right[l])
            elif l > r:
                ans.append(prefix_left[l] - prefix_left[r])
            else:
                ans.append(0)

        return ans