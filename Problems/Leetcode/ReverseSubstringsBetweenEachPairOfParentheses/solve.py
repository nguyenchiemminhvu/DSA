class Solution:
    def reverseParentheses(self, s: str) -> str:
        st = []
        for c in s:
            if c == ')':
                tmp = []
                while st and st[-1] != '(':
                    tmp.append(st.pop())
                st.pop()
                for ct in tmp:
                    st.append(ct)
            else:
                st.append(c)
        return "".join(st)