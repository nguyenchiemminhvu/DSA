from typing import List

class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m = len(matrix)
        n = len(matrix[0])

        def binary_search(arr: List[int], target: int) -> bool:
            left = 0
            right = len(arr) - 1
            while left <= right:
                mid = left + (right - left) // 2
                if target == arr[mid]:
                    return True
                if target < arr[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            return False

        for row in matrix:
            if binary_search(row, target):
                return True
        return False