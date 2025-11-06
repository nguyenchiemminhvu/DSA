class Solution:
    def isBalanced(self, num: str) -> bool:
        arr = [0, 0]
        for i in range(len(num)):
            arr[(i & 1)] += (ord(num[i]) - ord('0'))
        return arr[0] == arr[1]