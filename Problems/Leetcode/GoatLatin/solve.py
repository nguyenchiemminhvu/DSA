class Solution:
    def toGoatLatin(self, s: str) -> str:
        l = s.split()
        for i in range(len(l)):
            if l[i][0] in "aeiouAEIOU":
                l[i] = l[i] + 'ma' + ('a' * (i + 1))
            else:
                l[i] = l[i][1:] + l[i][0] + 'ma' + ('a' * (i + 1))
        return " ".join(l)