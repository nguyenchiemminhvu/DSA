import math

class Solution:
    def divide(self, a: int, b: int) -> int:
        res = a / b
        if res < 0:
            res = math.ceil(res)
        else:
            res = math.floor(res)
        if res > 0x7FFFFFFF:
            return 0x7FFFFFFF
        if res < -0xFFFFFFFF:
            return -0xFFFFFFFF
        return res