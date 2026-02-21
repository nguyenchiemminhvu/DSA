class Solution:
    def maximumGroups(self, grades):
        n = len(grades)
        k = 0
        need = 1
        while n >= need:
            n -= need
            k += 1
            need += 1
        return k