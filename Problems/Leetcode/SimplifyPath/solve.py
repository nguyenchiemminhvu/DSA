class Solution:
    def simplifyPath(self, path: str) -> str:
        st = []
        arr = path.split('/')
        for sub in arr:
            if not sub:
                continue
            if sub == '.':
                continue
            elif sub == '..':
                if st:
                    st.pop()
            else:
                st.append(sub)

        return "/" + "/".join(st)