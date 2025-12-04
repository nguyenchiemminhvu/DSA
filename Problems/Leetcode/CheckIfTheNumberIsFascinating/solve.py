class Solution:
    def isFascinating(self, n: int) -> bool:
        s = str(n) + str(n * 2) + str(n * 3)
        arr = []
        for c in s:
            if c == '0':
                return False
            arr.append(c)
        ss = set(arr)
        return len(ss) == len(arr) and ss == set('123456789')