class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:
        idx = []
        for i in range(len(s)):
            if s[i] == '(' or s[i] == ')':
                idx.append(i)
        
        st = []
        for i in range(len(idx)):
            if s[idx[i]] == ')':
                if st and s[st[-1]] == '(':
                    st.pop()
                else:
                    st.append(idx[i])
            else:
                st.append(idx[i])
        
        res = "".join([c for i, c in enumerate(s) if i not in st])
        return res