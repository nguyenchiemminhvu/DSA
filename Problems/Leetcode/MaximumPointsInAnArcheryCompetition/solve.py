from typing import List

class Solution:
    def maximumBobPoints(self, num_arrows: int, alice_arrows: List[int]) -> List[int]:
        bob_max_score = -1
        bob_arrows = [0] * 12
        tmp = [0] * 12

        def dfs(i:int, remain:int, score:int) -> None:
            nonlocal bob_max_score, bob_arrows
            if i == 0:
                tmp[0] = remain
                if score > bob_max_score:
                    bob_max_score = score
                    bob_arrows = tmp[:]
                tmp[0] = 0
                return
            
            dfs(i - 1, remain, score)

            if remain > alice_arrows[i]:
                tmp[i] = alice_arrows[i] + 1
                dfs(i - 1, remain - alice_arrows[i] - 1, score + i)
                tmp[i] = 0
        
        dfs(11, num_arrows, 0)
        return bob_arrows