class Solution:
    def minNumber(self, a: List[int], b: List[int]) -> int:      
        s = set(a) & set(b)
        if s:
            return min(s)
        temp = sorted([min(a), min(b)])
        res = temp[0] * 10 + temp[1]
        return res