from typing import List

class Solution:
    def bagOfTokensScore(self, tokens: List[int], power: int) -> int:
        n = len(tokens)
        tokens.sort()
        l, r = 0, n - 1
        cur_score = 0
        res = 0
        while l <= r:
            if power >= tokens[l]:
                cur_score += 1
                res = max(res, cur_score)
                power -= tokens[l]
                l += 1
            elif cur_score > 0:
                cur_score -= 1
                power += tokens[r]
                r -= 1
            else:
                break
        
        return res