class Solution:
    def digitSum(self, s: str, k: int) -> str:
        while len(s) > k:
            arr = [s[i:i+k] for i in range(0, len(s), k)]
            for i in range(len(arr)):
                val = 0
                for c in arr[i]:
                    val += int(c)
                arr[i] = str(val)
            s = "".join(arr)
        return s