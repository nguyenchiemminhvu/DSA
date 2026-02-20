class Solution:
    def maxConsecutiveAnswers(self, keys: str, k: int) -> int:
        n = len(keys)
        res = 0
        count_t = 0
        count_f = 0
        l = 0
        for r in range(n):
            if keys[r] == 'T':
                count_t += 1
            else:
                count_f += 1
            
            while min(count_t, count_f) > k:
                if keys[l] == 'T':
                    count_t -= 1
                else:
                    count_f -= 1
                l += 1
            
            if min(count_t, count_f) <= k:
                res = max(res, r - l + 1)
        
        return res