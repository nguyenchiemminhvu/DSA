from typing import List

class Solution:
    def numberOfWeakCharacters(self, properties: List[List[int]]) -> int:
        properties.sort(key=lambda x: (x[0], -x[1]))
        
        count = 0
        st = []
        for a, d in properties:
            while st:
                last_a, last_d = st[-1]
                if a > last_a and d > last_d:
                    count += 1
                    st.pop()
                else:
                    break
            st.append((a, d))

        return count