class Solution:
    def gcdOfStrings(self, a: str, b: str) -> str:
        prefix = []
        na, nb = len(a), len(b)
        for i in range(min(na, nb)):
            if a[i] != b[i]:
                break
            prefix.append(a[i])
        
        while prefix:
            np = len(prefix)
            if na % np == 0 and nb % np == 0:
                sa = "".join(prefix) * (na // np)
                sb = "".join(prefix) * (nb // np)
                if sa == a and sb == b:
                    break
            prefix.pop()
        
        return "".join(prefix)
