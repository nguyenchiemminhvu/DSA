from typing import List

class Solution:
    def asteroidCollision(self, asteroids: List[int]) -> List[int]:
        st = []
        for obj in asteroids:
            if obj > 0:
                st.append(obj)
            else:
                self_destroyed = False
                while st and st[-1] > 0:
                    if abs(st[-1]) < abs(obj):
                        st.pop()
                    elif abs(st[-1]) > abs(obj):
                        self_destroyed = True
                        break
                    else:
                        st.pop()
                        self_destroyed = True
                        break
                if not self_destroyed:
                    st.append(obj)
        return st