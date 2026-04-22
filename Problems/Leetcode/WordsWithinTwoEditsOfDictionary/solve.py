from typing import List

class Solution:
    def twoEditWords(self, queries: List[str], dictionary: List[str]) -> List[str]:
        res = []
        for query in queries:
            n = len(query)
            for word in dictionary:
                count_diff = 0
                for i in range(n):
                    if query[i] != word[i]:
                        count_diff += 1
                        if count_diff > 2:
                            break
                if count_diff <= 2:
                    res.append(query)
                    break
        return res