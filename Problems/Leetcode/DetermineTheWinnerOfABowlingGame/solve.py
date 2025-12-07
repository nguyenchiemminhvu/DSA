from typing import List

class Solution:
    def isWinner(self, player1: List[int], player2: List[int]) -> int:
        s1 = 0
        s2 = 0
        n = len(player1)
        for i in range(n):
            s1 += player1[i]
            s2 += player2[i]
            if i > 1:
                if player1[i - 1] == 10 or player1[i - 2] == 10:
                    s1 += player1[i]
                if player2[i - 1] == 10 or player2[i - 2] == 10:
                    s2 += player2[i]
            elif i > 0:
                if player1[i - 1] == 10:
                    s1 += player1[i]
                if player2[i - 1] == 10:
                    s2 += player2[i]
        
        if s1 > s2:
            return 1
        if s2 > s1:
            return 2
        return 0