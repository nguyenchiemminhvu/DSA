from collections import defaultdict
from typing import List

class Solution:
    def countTriplets(self, arr: List[int]) -> int:
        n = len(arr)

        # at the index j (1 to n) there are how many subarray xor value 'val'
        prefix_xor = defaultdict(lambda: defaultdict(int))

        for i in range(n):
            x = 0
            for j in range(i, n):
                x ^= arr[j]
                prefix_xor[i][x] += 1
        
        res = 0
        for i in range(n - 1):
            x = 0
            for j in range(i, -1, -1):
                x ^= arr[j]
                res += prefix_xor[i + 1][x]
        return res