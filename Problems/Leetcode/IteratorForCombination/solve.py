class CombinationIterator:

    def __init__(self, s: str, k: int):
        def count_bit(val: int) -> int:
            count = 0
            while val:
                val = val & (val - 1)
                count += 1
            return count
        
        self.arr = []
        n = len(s)
        nn = 1 << n
        for mask in range(nn):
            if count_bit(mask) != k:
                continue
            
            tmp = []
            for i in range(n):
                if (1 << i) & mask:
                    tmp.append(s[i])
            self.arr.append("".join(tmp))
        self.arr.sort()
        self.idx = 0

    def next(self) -> str:
        s = self.arr[self.idx]
        self.idx += 1
        return s

    def hasNext(self) -> bool:
        return self.idx < len(self.arr)

# Your CombinationIterator object will be instantiated and called as such:
# obj = CombinationIterator(characters, combinationLength)
# param_1 = obj.next()
# param_2 = obj.hasNext()