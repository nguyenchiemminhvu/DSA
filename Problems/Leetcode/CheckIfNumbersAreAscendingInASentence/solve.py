class Solution:
    def areNumbersAscending(self, s: str) -> bool:
        s += ' '
        arr = []
        val = 0
        for c in s:
            if c.isdigit():
                val = val * 10 + int(c)
            else:
                if val > 0:
                    arr.append(val)
                    val = 0
        for i in range(1, len(arr)):
            if arr[i] <= arr[i - 1]:
                return False
        return True