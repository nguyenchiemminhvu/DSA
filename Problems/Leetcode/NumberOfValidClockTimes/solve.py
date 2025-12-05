class Solution:
    def countTime(self, time: str) -> int:
        hours = [f"{i:02d}" for i in range(24)]
        minutes = [f"{i:02d}" for i in range(60)]

        count = 0
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
                    count += 1
        return count