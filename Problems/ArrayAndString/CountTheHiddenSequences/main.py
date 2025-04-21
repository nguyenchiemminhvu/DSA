# https://leetcode.com/problems/count-the-hidden-sequences/description/

from typing import List

class Solution:
    def numberOfArrays(self, differences: List[int], lower: int, upper: int) -> int:
        current = 0
        min_val = 0
        max_val = 0

        for diff in differences:
            current += diff
            min_val = min(min_val, current)
            max_val = max(max_val, current)

        # The full range needed by the constructed array
        total_range = max_val - min_val

        # The number of valid starting values that keep all values within bounds
        available_range = (upper - lower) - total_range + 1

        return max(available_range, 0)

if __name__ == "__main__":
    # Example usage
    solution = Solution()
    differences = [1, -3, 4]
    lower = 1
    upper = 6
    result = solution.numberOfArrays(differences, lower, upper)
    print(result)  # Output: 2