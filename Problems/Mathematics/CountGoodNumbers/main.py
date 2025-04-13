# https://leetcode.com/problems/count-good-numbers

class Solution:
    def countGoodNumbers(self, n: int) -> int:
        MOD = 10**9 + 7
        even_positions = (n + 1) // 2
        odd_positions = n // 2

        return (pow(5, even_positions, MOD) * pow(4, odd_positions, MOD)) % MOD

if __name__ == "__main__":
    # Example usage
    n = 50
    solution = Solution()
    result = solution.countGoodNumbers(n)
    print(result)  # Output: 564908303