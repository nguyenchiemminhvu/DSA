class Solution:
    def clearDigits(self, s: str) -> str:
        st = []
        for c in s:
            if c.isdigit():
                st.pop()
            else:
                st.append(c)
        return "".join(st)