from typing import List

class Solution:
    def areSimilar(self, mat: List[List[int]], k: int) -> bool:
        def shift_right(arr: List[int], k: int) -> List[int]:
            n = len(arr)
            return (arr[n-k:] + arr[0:n-k])
        
        def shift_left(arr: List[int], k: int) -> List[int]:
            n = len(arr)
            return (arr[k:] + arr[0:k])
        
        k %= len(mat[0])
        another = []
        is_left = True
        for i in range(len(mat)):
            if is_left:
                another.append(shift_left(mat[i], k))
            else:
                another.append(shift_right(mat[i], k))
        return mat == another