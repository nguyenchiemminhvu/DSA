class Solution:
    def reorderSpaces(self, text: str) -> str:
        arr = text.split()
        s = text.count(' ')
        n = len(arr)
        if n == 1:
            return arr[0] + ' ' * s
        return (' ' * (s // (n - 1))).join(arr) + ' ' * (s % (n - 1))