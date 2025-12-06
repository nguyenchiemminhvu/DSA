class Solution:
    def findMinimumOperations(self, s1: str, s2: str, s3: str) -> int:
        prefix = ""
        n1, n2, n3 = len(s1), len(s2), len(s3)
        n = min([n1, n2, n3])
        for i in range(n, 0, -1):
            if s1[:i] == s2[:i] == s3[:i]:
                prefix = s1[:i]
                n = len(prefix)
                break
        if prefix == "":
            return -1
        
        return n1 - n + n2 - n + n3 - n