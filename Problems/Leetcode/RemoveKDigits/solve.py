class Solution:
    def removeKdigits(self, num: str, k: int) -> str:
        n = len(num)
        st = []
        for c in num:
            while k and st and st[-1] > c:
                st.pop()
                k -= 1
            st.append(c)
        while k:
            st.pop()
            k -= 1
        i = 0
        while i < len(st) and st[i] == '0':
            i += 1
        res = "".join(st[i:])
        return '0' if not res else res