class Solution:
    def makeGood(self, s: str) -> str:
        st = []
        for c in s:
            if c.islower():
                if st and st[-1].isupper() and c == st[-1].lower():
                    st.pop()
                else:
                    st.append(c)
            elif c.isupper():
                if st and st[-1].islower() and c == st[-1].upper():
                    st.pop()
                else:
                    st.append(c)
        return "".join(st)