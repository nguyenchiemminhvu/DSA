class Solution:
    def numDifferentIntegers(self, word: str) -> int:
        return len(set(list(map(int, "".join([' ' if not w.isdigit() else w for w in word]).split()))))