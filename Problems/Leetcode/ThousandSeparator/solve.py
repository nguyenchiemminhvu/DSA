class Solution:
    def thousandSeparator(self, n: int) -> str:
        n = list(str(n))
        count = 0
        res = ""
        while n:
            res += n.pop()
            count += 1
            if count == 3:
                res += '.'
                count = 0
        if res[-1] == '.':
            res = res[:-1]
        return res[::-1]