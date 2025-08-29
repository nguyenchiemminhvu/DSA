# https://leetcode.com/problems/alice-and-bob-playing-flower-game/description/

class Solution:
    def flowerGame(self, n: int, m: int) -> int:
        odd_x = (n + 1) // 2
        even_x = n // 2

        odd_y = (m + 1) // 2
        even_y = m // 2

        return odd_x * even_y + even_x * odd_y

if __name__ == "__main__":
    s = Solution()
    print(s.flowerGame(2, 3))  # Output: 6
    print(s.flowerGame(3, 3))  # Output: 5
    