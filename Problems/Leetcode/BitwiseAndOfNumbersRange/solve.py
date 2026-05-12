class Solution:
    def rangeBitwiseAnd(self, left: int, right: int) -> int:
        count_shift = 0
        while left != right:
            left >>= 1
            right >>= 1
            count_shift += 1
        
        return left << count_shift