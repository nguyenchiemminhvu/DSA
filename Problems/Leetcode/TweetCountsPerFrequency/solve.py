from typing import List

class TweetCounts:

    def __init__(self):
        self.mp = {} # name -> [time]

    def recordTweet(self, name: str, time: int) -> None:
        if name not in self.mp:
            self.mp[name] = []
        self.mp[name].append(time)

    def getTweetCountsPerFrequency(self, freq: str, name: str, start: int, end: int) -> List[int]:
        def lower_bound(arr: List[int], target: int) -> int:
            na = len(arr)
            l, r, idx = 0, na - 1, na
            while l <= r:
                m = l + (r - l) // 2
                if arr[m] >= target:
                    idx = m
                    r = m - 1
                else:
                    l = m + 1
            return idx

        def upper_bound(arr: List[int], target: int) -> int:
            na = len(arr)
            l, r, idx = 0, na - 1, na
            while l <= r:
                m = l + (r - l) // 2
                if arr[m] > target:
                    idx = m
                    r = m - 1
                else:
                    l = m + 1
            return idx
        
        interval = 60
        if freq == "hour":
            interval = 3600
        elif freq == "day":
            interval = 86400
        
        n = int((end - start) / interval + 1)
        chunks = [0] * n

        arr = self.mp[name]
        arr.sort()

        for i in range(n):
            l = start + i * interval
            r = min(l + interval - 1, end)
            lower = lower_bound(arr, l)
            upper = upper_bound(arr, r)
            chunks[i] = upper - lower
        return chunks

# Your TweetCounts object will be instantiated and called as such:
# obj = TweetCounts()
# obj.recordTweet(tweetName,time)
# param_2 = obj.getTweetCountsPerFrequency(freq,tweetName,startTime,endTime)