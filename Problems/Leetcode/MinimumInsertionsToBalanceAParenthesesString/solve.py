class Solution:
    def minInsertions(self, s: str) -> int:
        st = []
        res = 0

        n = len(s)
        i = 0
        while i < n:
            if s[i] == '(':
                st.append(s[i])
            else:
                if i + 1 < n and s[i + 1] == ')':
                    res += int(not st)
                    i += 1
                else:
                    res += 1 + int(not st)
                
                if st:
                    st.pop()
            
            i += 1
        return res + len(st) * 2