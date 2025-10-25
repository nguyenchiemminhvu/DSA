class Solution:
    def minTimeToType(self, word: str) -> int:
        def min_cost(a:str, b:str) -> int:
            vals = [ord(a) - ord('a'), ord(b) - ord('a')]
            vals.sort()
            cost = min(vals[1] - vals[0], 26 - vals[1] + vals[0])
            return cost

        res = 0
        cur_key = 'a'
        for c in word:
            res += min_cost(cur_key, c)
            res += 1
            cur_key = c
        return res