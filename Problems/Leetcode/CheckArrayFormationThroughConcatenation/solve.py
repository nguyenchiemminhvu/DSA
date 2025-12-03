from typing import List

class Solution:
    def canFormArray(self, arr: List[int], p: List[List[int]]) -> bool:
        for row in p:
            try:
                start = arr.index(row[0])
            except:
                return False
            for val in row:
                if start >= len(arr) or val != arr[start]:
                    return False
                start += 1
        return True