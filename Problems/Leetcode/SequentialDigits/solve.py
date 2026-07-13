class Solution:
    def sequentialDigits(self, low: int, high: int) -> List[int]:
        res = []

        def F(val: int):
            if val > high:
                return
            
            if val >= low:
                res.append(val)
            
            last_digit = val % 10
            if last_digit == 9:
                return
            next_digit = last_digit + 1
            F(val * 10 + next_digit)
        
        for i in range(1, 9):
            F(i)
        res.sort()
        return res