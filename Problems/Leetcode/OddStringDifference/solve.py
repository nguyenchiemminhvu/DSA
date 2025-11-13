from typing import List

class Solution:
    def oddString(self, words: List[str]) -> str:
        f = {}
        for i, word in enumerate(words):
            diff = []
            for j in range(1, len(word)):
                diff.append(ord(word[j]) - ord(word[j - 1]))
            tdiff = tuple(diff)
            if tdiff not in f:
                f[tdiff] = [0, 0]
            f[tdiff][0] = i
            f[tdiff][1] += 1
        for k, v in f.items():
            if v[1] == 1:
                return words[v[0]]
        return ""