class Solution:
    def calculateScore(self, s: str) -> int:
        def get_reflection(val: int) -> int:
            return 25 - val
        
        s = [ord(c) - ord('a') for c in s]
        sts = [[] for _ in range(26)]

        res = 0
        for i, val in enumerate(s):
            ref = get_reflection(val)
            if sts[ref]:
                j = sts[ref].pop()
                res += i - j
            else:
                sts[val].append(i)
        return res