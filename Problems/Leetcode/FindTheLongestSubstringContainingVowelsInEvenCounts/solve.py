class Solution:
    def findTheLongestSubstring(self, s: str) -> int:
        n = len(s)
        vowel = set('aeiou')
        vowel_to_idx = { c: i for i, c in enumerate('aeiou') }

        res = 0
        mp = {}
        masks = [0] * 5
        mp[tuple(masks)] = -1
        for i, c in enumerate(s):
            if c in vowel:
                masks[vowel_to_idx[c]] = (masks[vowel_to_idx[c]] + 1) & 1
            
            state = tuple(masks)
            if state in mp:
                res = max(res, i - mp[state])
            else:
                mp[state] = i
        
        return res