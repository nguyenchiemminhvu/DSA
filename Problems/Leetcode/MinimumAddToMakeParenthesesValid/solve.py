class Solution:
    def minAddToMakeValid(self, s: str) -> int:
        st = []
        count = 0
        for c in s:
            if c == '(':
                st.append(c)
            else:
                if not st:
                    count += 1
                else:
                    st.pop()
        return count + len(st)