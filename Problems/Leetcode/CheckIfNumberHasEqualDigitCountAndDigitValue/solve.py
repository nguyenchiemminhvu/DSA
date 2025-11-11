from collections import Counter

class Solution:
    def digitCount(self, num: str) -> bool:
        arr = [int(val) for val in list(num)]
        f = Counter(arr)
        for i in range(len(arr)):
            if f[i] != arr[i]:
                return False

        return True