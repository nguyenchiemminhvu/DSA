from typing import List

class Solution:
    def findRelativeRanks(self, score: List[int]) -> List[str]:
        def rank_to_text(rank: int) -> str:
            if rank == 1:
                return 'Gold Medal'
            if rank == 2:
                return 'Silver Medal'
            if rank == 3:
                return 'Bronze Medal'
            return str(rank)
        
        ranks = sorted([(val, i) for i, val in enumerate(score)], key=lambda x: -x[0])
        for i, rank in enumerate(ranks):
            idx = rank[1]
            text = rank_to_text(i + 1)
            score[idx] = text
        return score