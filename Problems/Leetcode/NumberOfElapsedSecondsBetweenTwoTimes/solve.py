class Solution:
    def secondsBetweenTimes(self, startTime: str, endTime: str) -> int:
        def to_timestamp(s:str) -> int:
            h = int(s[:2])
            m = int(s[3:5])
            s = int(s[6:])
            return h * 3600 + m * 60 + s
        
        start = to_timestamp(startTime)
        end = to_timestamp(endTime)
        return end - start