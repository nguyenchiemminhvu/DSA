class Solution:
    def convertToBase7(self, num: int) -> str:
        if num == 0:
            return "0"
        
        base7_vals = ['0', '1', '2', '3', '4', '5', '6', '7']
        s = ""
        sign = (num < 0)
        num = abs(num)
        while num > 0:
            s += base7_vals[num % 7]
            num //= 7
        return ("-" if sign else "") + s[::-1]