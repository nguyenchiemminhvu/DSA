from typing import List
from collections import deque

class Solution:
    def countStudents(self, students: List[int], st: List[int]) -> int:
        st.reverse()

        count_unable = 0
        students = deque(students)
        while st and students and count_unable < len(students):
            if st[-1] == students[0]:
                count_unable = 0
                st.pop()
                students.popleft()
            else:
                count_unable += 1
                students.append(students.popleft())
        return count_unable