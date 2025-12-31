class Solution:
    def canBeValid(self, s: str, locked: str) -> bool:
        n = len(s)
        if n & 1:
            return False
        
        st_open = []
        st_unlock = []
        for i, c in enumerate(s):
            if locked[i] == '0':
                st_unlock.append(i)
            else:
                if c == '(':
                    st_open.append(i)
                else:
                    if st_open:
                        st_open.pop()
                    elif st_unlock:
                        st_unlock.pop()
                    else:
                        return False
        if st_open and not st_unlock:
            return False
        
        while st_open:
            if not st_unlock or st_unlock[-1] < st_open[-1]:
                return False
            st_open.pop()
            st_unlock.pop()
        return not st_open or len(st_unlock) % 2 == 0