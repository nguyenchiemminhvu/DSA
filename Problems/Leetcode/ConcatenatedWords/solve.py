from typing import List

class Solution:
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
        word_set = set(words)

        def can_form(word: str) -> bool:
            mem = {}
            def F(i: int) -> bool:
                if i < 0:
                    return False
                if i == 0:
                    return True
                if i in mem:
                    return mem[i]
                res = False
                for j in range(i):
                    sub = word[j:i]
                    if sub in word_set:
                        res = res or F(j)
                mem[i] = res
                return res
            return F(len(word))

            # dp = [False] * (len(word) + 1)
            # dp[0] = True
            # for i in range(1, len(word) + 1):
            #     for j in range(i):
            #         if not dp[j]:
            #             continue
            #         if word[j:i] in word_set:
            #             dp[i] = True
            #             break
            # return dp[len(word)]

        res = []
        for word in words:
            word_set.remove(word)
            if can_form(word):
                res.append(word)
            word_set.add(word)
        return res