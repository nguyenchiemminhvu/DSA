class Solution:
    def minLength(self, s: str) -> int:
        st = []
        for c in s:
            if c == 'B' and st and st[-1] == 'A':
                st.pop()
            elif c == 'D' and st and st[-1] == 'C':
                st.pop()
            else:
                st.append(c)
        return len(st)