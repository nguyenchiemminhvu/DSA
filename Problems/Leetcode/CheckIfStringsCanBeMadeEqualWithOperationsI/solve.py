class Solution:
    def canBeEqual(self, s1: str, s2: str) -> bool:
        part1 = sorted([s1[0], s1[2]])
        part2 = sorted([s2[0], s2[2]])
        part3 = sorted([s1[1], s1[3]])
        part4 = sorted([s2[1], s2[3]])
        return part1 == part2 and part3 == part4