class Solution:
    def hasAllCodes(self, s: str, k: int) -> bool:
        sub_arr = set()
        n = len(s)
        for i in range(n - k + 1):
            sub_arr.add(s[i:i+k])
        
        return len(sub_arr) == (1 << k)