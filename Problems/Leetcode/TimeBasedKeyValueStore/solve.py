from typing import List, Tuple

class TimeMap:

    def __init__(self):
        self.data = {} # key -> (timestamp, value)

    def set(self, key: str, value: str, timestamp: int) -> None:
        if key not in self.data:
            self.data[key] = []
        self.data[key].append((timestamp, value))

    def get(self, key: str, timestamp: int) -> str:
        def bin_search(arr: List[Tuple[int]], t: int) -> int:
            n = len(arr)
            l, r = 0, n - 1
            idx = n
            while l <= r:
                m = l + (r - l) // 2
                if arr[m][0] > t:
                    idx = m
                    r = m - 1
                else:
                    l = m + 1
            return idx
        
        if key not in self.data:
            return ""
        
        upper = bin_search(self.data[key], timestamp)
        upper -= 1
        if upper >= 0:
            return self.data[key][upper][1]
        return ""

# Your TimeMap object will be instantiated and called as such:
# obj = TimeMap()
# obj.set(key,value,timestamp)
# param_2 = obj.get(key,timestamp)