import string

class Solution:
    def checkIfPangram(self, sentence: str) -> bool:
        d = {}
        for c in string.ascii_lowercase:
            d[c] = 1
        for c in sentence:
            d[c] -= 1
        return all((v <= 0) for k, v in d.items())