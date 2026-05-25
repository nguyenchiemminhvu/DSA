from typing import List

class Solution:
    def maximumSum(self, arr: List[int]) -> int:
        n = len(arr)

        max_all = arr[0]
        cur_without_del = arr[0]
        cur_with_del = arr[0]
        for i in range(1, n):
            cur_with_del = max(cur_with_del + arr[i], cur_without_del)
            cur_without_del = max(cur_without_del + arr[i], arr[i])
            max_all = max(max_all, cur_with_del, cur_without_del)
        return max_all