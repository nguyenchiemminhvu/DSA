from typing import List

class Solution:
    def calculateTax(self, brackets: List[List[int]], income: int) -> float:
        idx = 0
        res = 0
        prev_upper = 0
        remain = income
        while remain > 0:
            cur_upper, cur_percent = brackets[idx]
            taxed_income = min(income, cur_upper) - prev_upper
            remain -= taxed_income
            res += taxed_income * cur_percent / 100
            prev_upper = cur_upper
            idx += 1
        return res