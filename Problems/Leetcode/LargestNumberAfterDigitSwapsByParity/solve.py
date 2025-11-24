from collections import deque

class Solution:
    def largestInteger(self, num: int) -> int:
        arr = deque()
        while num:
            arr.appendleft(num % 10)
            num //= 10
        
        odd_idx = []
        even_idx = []
        for i, val in enumerate(arr):
            if val & 1:
                odd_idx.append(i)
            else:
                even_idx.append(i)
        
        temp = sorted([arr[i] for i in odd_idx], reverse=True)
        for i, val in enumerate(odd_idx):
            arr[val] = temp[i]
        
        temp = sorted([arr[i] for i in even_idx], reverse=True)
        for i, val in enumerate(even_idx):
            arr[val] = temp[i]

        res = 0
        for val in arr:
            res = res * 10 + val
        return res