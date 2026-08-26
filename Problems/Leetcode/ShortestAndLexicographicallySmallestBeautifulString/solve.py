class Solution:
    def shortestBeautifulSubstring(self, s: str, k: int) -> str:
        n = len(s)
        found_len = float('inf')
        found_sub = ''
        count = 0
        l = 0
        for r in range(n):
            count += int(s[r] == '1')
            while count > k:
                count -= int(s[l] == '1')
                l += 1
            
            while count == k and s[l] == '0':
                l += 1
            
            if count == k:
                dist = r - l + 1
                cur_sub = s[l:r+1]
                if dist < found_len:
                    found_len = dist
                    found_sub = cur_sub
                elif dist == found_len:
                    found_sub = min(found_sub, cur_sub)
        
        return found_sub