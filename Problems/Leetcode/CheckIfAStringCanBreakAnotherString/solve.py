class Solution:
    def checkIfCanBreak(self, s1: str, s2: str) -> bool:
        s1 = sorted(list(s1))
        s2 = sorted(list(s2))

        def check_break(s1:str, s2:str) -> bool:
            n = len(s1)
            for i in range(n):
                if s1[i] < s2[i]:
                    return False
            return True
        
        return check_break(s1, s2) or check_break(s2, s1)