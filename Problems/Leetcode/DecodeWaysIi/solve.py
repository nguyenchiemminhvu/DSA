class Solution:
    def numDecodings(self, s: str) -> int:
        mod = 10**9+7
        n = len(s)

        mem = {}
        def F(i: int) -> int:
            if i > n:
                return 0
            if i == n:
                return 1
            if s[i] == '0':
                return 0
            
            if i in mem:
                return mem[i]

            ways = 0
            # pick 1 char
            ch = s[i]
            ways += (9 if ch == '*' else 1) * F(i + 1)

            # pick 2 chars
            if i < n - 1:
                ch1, ch2 = s[i], s[i + 1]
                if ch1 == '*' and ch2 == '*':
                    ways += 15 * F(i + 2)
                else:
                    if ch1 == '*':
                        ways += (2 if int(ch2) <= 6 else 1) * F(i + 2)
                    elif ch2 == '*':
                        if ch1 == '1':
                            ways += 9 * F(i + 2)
                        if ch1 == '2':
                            ways += 6 * F(i + 2)
                    else:
                        if 10 <= int(ch1 + ch2) <= 26:
                            ways += F(i + 2)
            mem[i] = ways % mod
            return ways % mod
        
        return F(0)