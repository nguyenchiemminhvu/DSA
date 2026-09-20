class Solution:
    def minSwaps(self, grid: list[list[int]]) -> int:
        n = len(grid)

        arr = []
        for row in grid:
            count = 0
            for i in range(n - 1, -1, -1):
                if row[i] == 1:
                    break
                count += 1
            arr.append(count)
        
        swaps = 0
        
        for i in range(n - 1):
            required_zeros = n - 1 - i
            
            found = -1
            for j in range(i, n):
                if arr[j] >= required_zeros:
                    found = j
                    break
            
            if found == -1:
                return -1
            
            swaps += found - i
            arr.insert(i, arr.pop(found))
            
        return swaps
