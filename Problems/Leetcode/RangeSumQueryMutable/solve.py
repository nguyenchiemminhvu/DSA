from typing import List

class BIT:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)
    
    def add(self, idx, val):
        idx += 1
        while idx <= self.n:
            self.tree[idx] += val
            idx += (idx & -idx)
    
    def query(self, idx):
        idx += 1
        s = 0
        while idx > 0:
            s += self.tree[idx]
            idx -= (idx & -idx)
        return s
    
    def range_query(self, left, right):
        if left > right:
            return 0
        return self.query(right) - self.query(left - 1)

class NumArray:

    def __init__(self, nums: List[int]):
        self.n = len(nums)
        self.nums = nums[:]
        self.bit = BIT(self.n)
        for i, val in enumerate(nums):
            self.bit.add(i, val)

    def update(self, index: int, val: int) -> None:
        delta = val - self.nums[index]
        self.nums[index] = val
        self.bit.add(index, delta)

    def sumRange(self, left: int, right: int) -> int:
        return self.bit.range_query(left, right)


# Your NumArray object will be instantiated and called as such:
# obj = NumArray(nums)
# obj.update(index,val)
# param_2 = obj.sumRange(left,right)