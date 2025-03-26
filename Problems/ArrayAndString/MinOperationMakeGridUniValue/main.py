# https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/

class Solution:
    def minOperations(self, grid: List[List[int]], x: int) -> int:
        arr = [val for row in grid for val in row]
        arr.sort()
        
        for val in arr:
            if (val - arr[0]) % x != 0:
                return -1

        med = arr[len(arr) // 2]
        count = 0
        for val in arr:
            count += abs(val - med) / x
        return int(count)