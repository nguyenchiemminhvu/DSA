from typing import List
from collections import defaultdict

class UndergroundSystem:
    def __init__(self):
        # self.info[start][end] -> (sum, count)
        self.info = defaultdict(lambda: defaultdict(lambda: (0, 0)))
        self.track = defaultdict(list) # track[id] -> [start, time]

    def checkIn(self, user: int, station: str, t: int) -> None:
        self.track[user] = [station, t]

    def checkOut(self, user: int, station: str, t: int) -> None:
        if user in self.track:
            start, time = self.track[user]
            self.track.pop(user)
            (s, count) = self.info[start][station]
            s += t - time
            count += 1
            self.info[start][station] = (s, count)

    def getAverageTime(self, start_station: str, end_station: str) -> float:
        avg = 0.0
        if start_station in self.info:
            if end_station in self.info[start_station]:
                s, count = self.info[start_station][end_station]
                avg = s / count
        return avg


# Your UndergroundSystem object will be instantiated and called as such:
# obj = UndergroundSystem()
# obj.checkIn(id,stationName,t)
# obj.checkOut(id,stationName,t)
# param_3 = obj.getAverageTime(startStation,endStation)