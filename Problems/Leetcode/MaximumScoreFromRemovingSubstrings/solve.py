from typing import Tuple

class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        def remove(s:str, pattern:str, score:int) -> Tuple[str]:
            st = []
            sum_score = 0
            for c in s:
                if c != pattern[1]:
                    st.append(c)
                else:
                    if st and st[-1] == pattern[0]:
                        sum_score += score
                        st.pop()
                    else:
                        st.append(c)
            return ("".join(st), str(sum_score))
        
        if x > y:
            s, score1 = remove(s, 'ab', x)
            s, score2 = remove(s, 'ba', y)
            return int(score1) + int(score2)
        else:
            s, score1 = remove(s, 'ba', y)
            s, score2 = remove(s, 'ab', x)
            return int(score1) + int(score2)