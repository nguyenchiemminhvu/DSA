class Solution:
    def bestClosingTime(self, customers: str) -> int:
        n = len(customers)
        suffix_y = [0] * n
        count_y = 0
        for i in range(n - 1, -1, -1):
            if customers[i] == 'Y':
                count_y += 1
            suffix_y[i] = count_y
        
        min_pen = float('inf')
        close_time = 0
        count_n = 0
        for i in range(n):
            if min_pen > count_n + suffix_y[i]:
                min_pen = count_n + suffix_y[i]
                close_time = i
            if customers[i] == 'N':
                count_n += 1
        if min_pen > count_n:
            close_time = n
        return close_time