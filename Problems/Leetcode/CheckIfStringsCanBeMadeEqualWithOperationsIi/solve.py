class Solution:
    def checkStrings(self, s1: str, s2: str) -> bool:
        n = len(s1)
        sub1 = [s1[i] for i in range(0, n, 2)]
        sub2 = [s1[i] for i in range(1, n, 2)]

        sub3 = [s2[i] for i in range(0, n, 2)]
        sub4 = [s2[i] for i in range(1, n, 2)]

        sub1.sort()
        sub2.sort()
        sub3.sort()
        sub4.sort()

        return sub1 == sub3 and sub2 == sub4