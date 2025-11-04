class Solution:
    def isLongPressedName(self, s: str, t: str) -> bool:
        idx_s = 0
        idx_t = 0
        ns = len(s)
        nt = len(t)
        prev = '#'
        while idx_s < ns and idx_t < nt:
            if s[idx_s] == t[idx_t]:
                prev = s[idx_s]
                idx_s += 1
                idx_t += 1
            else:
                if t[idx_t] != prev:
                    return False
                idx_t += 1
        while idx_t < nt:
            if t[idx_t] != prev:
                return False
            idx_t += 1
        return idx_s == ns and idx_t == nt