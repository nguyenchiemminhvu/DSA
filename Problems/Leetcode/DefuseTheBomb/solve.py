from typing import List

class Solution:
    def decrypt(self, code: List[int], k: int) -> List[int]:
        n = len(code)
        new_code = [0] * n
        if k == 0:
            return new_code
        
        prefix = code * 2
        for i in range(1, len(prefix)):
            prefix[i] += prefix[i - 1]
        
        for i in range(n):
            if k < 0:
                new_code[i] = prefix[i + n - 1] - prefix[i + n + k] + code[(i + k) % n]
            else:
                new_code[i] = prefix[i + k] - prefix[i]

        return new_code