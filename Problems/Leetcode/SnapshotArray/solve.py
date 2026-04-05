from typing import List

class SnapshotArray:

    def __init__(self, length: int):
        self.n = length
        self.snap_id = 0
        self.snaps = [[[0, 0]] for _ in range(length)]

    def set(self, index: int, val: int) -> None:
        if self.snaps[index][-1][0] == self.snap_id:
            self.snaps[index][-1][1] = val
        else:
            self.snaps[index].append([self.snap_id, val])

    def snap(self) -> int:
        self.snap_id += 1
        return self.snap_id - 1

    def get(self, index: int, snap_id: int) -> int:
        def lower_bound(arr, target):
            left, right = 0, len(arr)
            while left < right:
                mid = (left + right) // 2
                if arr[mid][0] < target:
                    left = mid + 1
                else:
                    right = mid
            return left
        
        arr = self.snaps[index]
        idx = lower_bound(arr, snap_id)
        
        if idx < len(arr) and arr[idx][0] == snap_id:
            return arr[idx][1]
        return arr[idx - 1][1]