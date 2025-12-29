from typing import List

class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        cars = sorted([pair for pair in zip(position, speed)], key=lambda x: x[0])
        
        count = 0
        st = []
        n = len(cars)
        cur_max_time = 0
        for i in range(n - 1, -1, -1):
            pos, s = cars[i]
            time = (target - pos) / s
            if st and cur_max_time < time:
                count += 1
                st = []
                cur_max_time = 0
            cur_max_time = max(cur_max_time, time)
            st.append(time)
        if st:
            count += 1
        return count