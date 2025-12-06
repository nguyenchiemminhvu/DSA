class Solution:
    def maximumTime(self, time: str) -> str:
        hours = list(reversed([f"{i:02d}" for i in range(24)]))
        minutes = list(reversed([f"{i:02d}" for i in range(60)]))
        for h in hours:
            for m in minutes:
                t = h + ":" + m
                valid = True
                for i in range(5):
                    if time[i] != '?':
                        if time[i] != t[i]:
                            valid = False
                            break
                if valid:
                    return t
        return ""