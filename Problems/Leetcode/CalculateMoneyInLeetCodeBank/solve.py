class Solution:
    def totalMoney(self, n: int) -> int:
        def sum_a_to_b(a:int, b:int) -> int:
            return (b - a + 1) * (a + b) // 2

        res = 0
        week_count = 1
        while n >= 7:
            n -= 7
            res += sum_a_to_b(week_count, week_count + 6)
            week_count += 1
        if n > 0:
            res += sum_a_to_b(week_count, week_count + n - 1)
        return res