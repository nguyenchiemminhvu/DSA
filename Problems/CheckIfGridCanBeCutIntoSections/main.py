# https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/

from typing import List

class Solution:
    def checkValidCuts(self, n: int, rectangles: List[List[int]]) -> bool:
        sorted_hor = [[rect[0], rect[2]] for rect in rectangles]
        sorted_ver = [[rect[1], rect[3]] for rect in rectangles]

        sorted_hor.sort()
        merged_hor = [sorted_hor[0]]
        for start, end in sorted_hor[1:]:
            if (merged_hor[-1][1] > start):
                merged_hor[-1][1] = max(merged_hor[-1][1], end)
            else:
                merged_hor.append([start, end])
        if (len(merged_hor) >= 3):
            return True

        sorted_ver.sort()
        merged_ver = [sorted_ver[0]]
        for start, end in sorted_ver[1:]:
            if (merged_ver[-1][1] > start):
                merged_ver[-1][1] = max(merged_ver[-1][1], end)
            else:
                merged_ver.append([start, end])
        if (len(merged_ver) >= 3):
            return True

        return False

if __name__ == "__main__":
    solution = Solution()
    n = 5
    rectangles = [
        [0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]
    ]
    result = solution.checkValidCuts(n, rectangles)
    print("Can the grid be cut into valid sections?", result)
