class Solution:
    def distanceTraveled(self, main_tank: int, extra_tank: int) -> int:
        res = 0
        while main_tank >= 5:
            main_tank -= 5
            if extra_tank:
                extra_tank -= 1
                main_tank += 1
            res += 50
        return res + main_tank * 10