from typing import List

class Solution:
    def findMissingAndRepeatedValues(self, grid: List[List[int]]) -> List[int]:
        repeated_val = 0
        actual_sum = 0
        actual_square_sum = 0
        for row in grid:
            for val in row:
                repeated_val ^= val
                actual_sum += val
                actual_square_sum += val ** 2
        
        n = len(grid) ** 2
        expected_sum = n * (n + 1) // 2
        expected_square_sum = n * (n + 1) * (2 * n + 1) // 6
        
        # Let's say the repeated value is 'a' and missing value is 'b'
        # actual_sum = expected_sum + a - b
        # actual_square_sum = expected_square_sum + a² - b²
        
        sum_diff = actual_sum - expected_sum  # a - b
        square_sum_diff = actual_square_sum - expected_square_sum  # a² - b²
        
        # a² - b² = (a + b)(a - b)
        # So: a + b = (a² - b²) / (a - b)
        sum_ab = square_sum_diff // sum_diff  # a + b
        
        # Now we have:
        # a - b = sum_diff
        # a + b = sum_ab
        # Solving: a = (sum_diff + sum_ab) / 2, b = (sum_ab - sum_diff) / 2
        
        repeated = (sum_diff + sum_ab) // 2
        missing = (sum_ab - sum_diff) // 2
        
        return [repeated, missing]