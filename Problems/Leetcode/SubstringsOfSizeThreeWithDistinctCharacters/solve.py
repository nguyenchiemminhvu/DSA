class Solution:
    def countGoodSubstrings(self, s: str) -> int:
        res = 0
        counter = {}
        n = len(s)
        left, right = 0, 0
        while right < n:
            counter[s[right]] = counter.get(s[right], 0) + 1
            if right - left + 1 > 3:
                counter[s[left]] -= 1
                if counter[s[left]] <= 0:
                    counter.pop(s[left])
                left += 1
            
            if right - left + 1 == 3 and len(counter.keys()) == 3:
                res += 1
            right += 1
        return res