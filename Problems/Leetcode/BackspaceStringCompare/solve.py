class Solution:
    def backspaceCompare(self, s: str, t: str) -> bool:
        sts = []
        for c in s:
            if c == '#':
                if sts:
                    sts.pop()
            else:
                sts.append(c)

        stt = []
        for c in t:
            if c == '#':
                if stt:
                    stt.pop()
            else:
                stt.append(c)
        
        return "".join(sts) == "".join(stt)