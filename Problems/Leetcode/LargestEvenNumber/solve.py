class Solution:
    def largestEven(self, s: str) -> str:
        arr = list(map(int, list(s)))
        while arr and arr[-1] & 1:
            arr.pop()
        return "".join(list(map(str, arr)))