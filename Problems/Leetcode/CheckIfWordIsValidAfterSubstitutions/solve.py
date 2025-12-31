class Solution:
    def isValid(self, s: str) -> bool:
        st = []
        for c in s:
            if c == 'c':
                if len(st) >= 2 and st[-1] == 'b' and st[-2] == 'a':
                    st.pop()
                    st.pop()
                else:
                    return False
            else:
                st.append(c)
        return not st