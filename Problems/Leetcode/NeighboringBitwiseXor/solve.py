from typing import List

class Solution:
    def doesValidArrayExist(self, derived: List[int]) -> bool:
        n = len(derived)

        if n == 1:
            # 0 ^ 0, 1 ^ 1 => must be 0
            if derived[0] == 0:
                return True
            else:
                return False
        
        def testing(val1, val2) -> bool:
            arr = [0] * n
            arr[0], arr[1] = val1, val2
            for i in range(2, n):
                arr[i] = derived[i - 1] ^ arr[i - 1]
            return arr[-1] ^ arr[0] == derived[-1]

        if derived[0] == 0:
            # 0 ^ 0, 1 ^ 1
            return testing(0, 0) or testing(1, 1)
        else:
            # 0 ^ 1, 1 ^ 0
            return testing(0, 1) or testing(1, 0)
        
        return False