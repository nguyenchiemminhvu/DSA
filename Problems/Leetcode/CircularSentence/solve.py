class Solution:
    def isCircularSentence(self, s: str) -> bool:
        words = s.split()
        words.append(words[0])
        for i in range(1, len(words)):
            if words[i - 1][-1] != words[i][0]:
                return False
        return True