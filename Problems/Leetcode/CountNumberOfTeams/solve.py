from typing import List

class Solution:
    def numTeams(self, rating: List[int]) -> int:
        n = len(rating)
        res = 0
        
        for i in range(n):
            left_smaller, left_greater = 0, 0
            right_smaller, right_greater = 0, 0

            for j in range(i):
                left_smaller += int(rating[j] < rating[i])
                left_greater += int(rating[j] > rating[i])
            
            for j in range(i + 1, n):
                right_smaller += int(rating[j] < rating[i])
                right_greater += int(rating[j] > rating[i])
            
            res += (left_smaller * right_greater)
            res += (left_greater * right_smaller)
            
        return res
