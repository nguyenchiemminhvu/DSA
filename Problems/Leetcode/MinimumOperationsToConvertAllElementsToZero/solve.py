from typing import List

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        count = 0
        st = []
        for val in nums:
            while st and st[-1] > val:
                temp = st[-1]
                if temp == 0:
                    break
                while st and st[-1] == temp:
                    st.pop()
                count += 1
            st.append(val)
        
        while st:
            temp = st[-1]
            if temp == 0:
                break
            while st and st[-1] == temp:
                st.pop()
            count += 1
        return count