class Solution:
    def appendCharacters(self, s: str, t: str) -> int:
        ns = len(s)
        nt = len(t)
        i_s = i_t = 0
        while i_s < ns and i_t < nt:
            if s[i_s] == t[i_t]:
                i_s += 1
                i_t += 1
            else:
                i_s += 1
        return nt - i_t