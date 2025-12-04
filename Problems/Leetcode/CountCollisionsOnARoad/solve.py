class Solution:
    def countCollisions(self, directions: str) -> int:
        res = 0
        n = len(directions)

        count_right = 0
        for i in range(n):
            c = directions[i]
            if c == 'R':
                count_right += 1
            else:
                res += count_right
                count_right = 0
        
        count_left = 0
        for i in range(n - 1, -1, -1):
            c = directions[i]
            if c == 'L':
                count_left += 1
            else:
                res += count_left
                count_left = 0

        return res