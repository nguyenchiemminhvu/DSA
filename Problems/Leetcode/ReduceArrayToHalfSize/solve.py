from typing import List

class Solution:
    def minSetSize(self, arr: List[int]) -> int:
        f = {}
        for val in arr:
            f[val] = f.get(val, 0) + 1
        keys = list(sorted(f.keys(), key=lambda x: -f[x]))
        print(keys)

        n = len(arr)
        expected = n // 2
        count = 0
        while n > expected:
            n -= f[keys[count]]
            count += 1

        return count