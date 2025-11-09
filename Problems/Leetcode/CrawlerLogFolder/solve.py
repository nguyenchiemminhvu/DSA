from typing import List

class Solution:
    def minOperations(self, logs: List[str]) -> int:
        st = []
        for log in logs:
            folder = log[0:len(log) - 1]
            if folder == '.':
                pass
            elif folder == '..':
                if st:
                    st.pop()
            else:
                st.append(folder)
        
        return len(st)