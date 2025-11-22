from typing import List

class Solution:
    def numberOfAlternatingGroups(self, colors: List[int]) -> int:
        colors.extend([colors[0], colors[1]])
        count = 0
        for i in range(1, len(colors) - 1):
            if colors[i - 1] != colors[i] != colors[i + 1]:
                count += 1