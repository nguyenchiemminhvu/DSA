class Solution:
    def minSwaps(self, s: str) -> int:
        count_open = 0
        swap = 0
        for c in s:
            if c == '[':
                count_open += 1
            else:
                if count_open > 0:
                    count_open -= 1
                else:
                    swap += 1
                    count_open += 1
        return swap