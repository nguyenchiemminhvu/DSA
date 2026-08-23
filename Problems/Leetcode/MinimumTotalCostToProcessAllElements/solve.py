class Solution:
    def minimumCost(self, nums: list[int], k: int) -> int:
        MOD = 10**9 + 7

        resources = k
        operations = 0
        cost = 0

        for need in nums:
            if resources < need:
                diff = need - resources
                count = (diff + k - 1) // k
                first = operations + 1
                last = operations + count

                cost += count * (first + last) // 2
                cost %= MOD

                operations += count

                resources += count * k

            resources -= need

        return cost