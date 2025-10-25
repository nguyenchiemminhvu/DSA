class Solution:
    def sumGame(self, num: str) -> bool:
        left = 0
        var_left = 0
        right = 0
        var_right = 0
        n = len(num)
        for i in range(n // 2):
            if num[i] != '?':
                left += ord(num[i]) - ord('0')
            else:
                var_left += 1

        for i in range(n // 2, n):
            if num[i] != '?':
                right += ord(num[i]) - ord('0')
            else:
                var_right += 1

        if var_left + var_right == 0:
            return left != right
        if (var_left + var_right) % 2 == 1:
            return True

        if var_left == var_right:
            return left != right
        
        return 2 * (left - right) != 9 * (var_right - var_left)