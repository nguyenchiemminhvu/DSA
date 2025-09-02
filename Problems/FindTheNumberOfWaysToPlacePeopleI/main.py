# https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/description/

from typing import List

class Solution:
    def numberOfPairs(self, points: List[List[int]]) -> int:
        # Sort by x ascending, if equal x then by y descending
        points.sort(key=lambda p: (p[0], -p[1]))

        count = 0
        n = len(points)

        for i in range(n):
            for j in range(i + 1, n):
                x1, y1 = points[i]
                x2, y2 = points[j]

                if y1 < y2:
                    continue

                flag = True
                for k in range(i + 1, n):
                    if k == j:
                        continue

                    x3, y3 = points[k]
                    if x1 <= x3 <= x2 and y2 <= y3 <= y1:
                        flag = False
                        break

                if flag:
                    count += 1

        return count

if __name__ == "__main__":
    solution = Solution()
    points = [[1, 2], [2, 1], [3, 3]]
    print(solution.numberOfPairs(points))