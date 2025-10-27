class Solution:
    def minimumSwap(self, s1: str, s2: str) -> int:
        count_x_y = 0
        count_y_x = 0
        for i in range(len(s1)):
            if s1[i] == 'x' and s2[i] == 'y':
                count_x_y += 1
            if s1[i] == 'y' and s2[i] == 'x':
                count_y_x += 1
        if (count_x_y + count_y_x) & 1:
            return -1
        res = count_x_y // 2 + count_y_x // 2
        res += (count_x_y % 2) + (count_y_x % 2)
        
        return res