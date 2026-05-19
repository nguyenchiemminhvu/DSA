class Solution:
    def pushDominoes(self, s: str) -> str:
        n = len(s)

        ops = [(-1, 'L')]
        for i in range(n):
            if s[i] != '.':
                ops.append((i, s[i]))
        ops.append((n, 'R'))

        res = list(s)
        for i in range(1, len(ops)):
            i1, ch1 = ops[i - 1]
            i2, ch2 = ops[i]
            if ch1 == ch2: # L..L or R..R
                for j in range(i1 + 1, i2):
                    res[j] = ch1
            elif ch1 == 'R' and ch2 == 'L':
                l, r = i1 + 1, i2 - 1
                while l < r:
                    res[l] = 'R'
                    res[r] = 'L'
                    l += 1
                    r -= 1
        return "".join(res)