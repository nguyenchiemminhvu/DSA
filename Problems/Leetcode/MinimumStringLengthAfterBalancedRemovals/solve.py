class Solution:
    def minLengthAfterRemovals(self, s: str) -> int:
        st = []
        for c in s:
            if c == 'b':
                if st and st[-1] == 'a':
                    st.pop()
                else:
                    st.append(c)
            else:
                if st and st[-1] == 'b':
                    st.pop()
                else:
                    st.append(c)
        return len(st)