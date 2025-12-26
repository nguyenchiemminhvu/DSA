from typing import List

class Solution:
    def validateStackSequences(self, pushed: List[int], popped: List[int]) -> bool:
        st = []
        ip = 0
        for val in pushed:
            st.append(val)
            while st and st[-1] == popped[ip]:
                st.pop()
                ip += 1
        
        while st:
            val = st.pop()
            if val != popped[ip]:
                return False
            ip += 1
        return True