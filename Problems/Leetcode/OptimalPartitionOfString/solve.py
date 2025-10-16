class Solution:
    def partitionString(self, s: str) -> int:
        s += s[-1]
        check = set()
        count = 0
        for c in s:
            if c in check:
                count += 1
                check.clear()
            check.add(c)
        return count