from typing import List

class Solution:
    def getMaxLen(self, nums: List[int]) -> int:
        def split_list_by_zeros(arr: List[int]) -> List[List[int]]:
            chunks = []
            chunk = []
            for val in nums:
                if val == 0:
                    if chunk:
                        chunks.append(chunk)
                    chunk = []
                else:
                    chunk.append(val)
            if chunk:
                chunks.append(chunk)
            return chunks
        
        def get_max_len_in_chunk(arr: List[int]) -> int:
            d = [] # index of negative values
            for i, val in enumerate(arr):
                if val < 0:
                    d.append(i)
            if len(d) % 2 == 0:
                return len(arr)
            
            sub_left = d[-1]
            sub_right = len(arr) - d[0] - 1
            return max(sub_left, sub_right)
        
        chunks = split_list_by_zeros(nums)
        res = 0
        for chunk in chunks:
            res = max(res, get_max_len_in_chunk(chunk))
        return res