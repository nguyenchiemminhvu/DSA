class Solution:
    def stringSequence(self, target: str) -> List[str]:
        res = []
        
        n = len(target)
        cur = ['a']
        i = 0
        while i < n:
            res.append(''.join(cur))
            while cur[i] != target[i]:
                cur[i] = chr(((ord(cur[i]) - ord('a') + 1) % 26) + ord('a'))
                res.append(''.join(cur))
            
            cur.append('a')
            i += 1
        
        return res