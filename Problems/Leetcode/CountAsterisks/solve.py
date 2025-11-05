class Solution:
    def countAsterisks(self, s: str) -> int:
        count = 0
        enabled = False
        for c in s:
            if c == '|':
                enabled = not enabled
            else:
                if c == '*' and not enabled:
                    count += 1
        return count