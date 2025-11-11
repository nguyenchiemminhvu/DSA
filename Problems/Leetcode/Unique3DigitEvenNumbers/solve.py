from typing import List

class Solution:
    def totalNumbers(self, digits: List[int]) -> int:
        n = len(digits)
        s = set()
        ss = set()
        temp = []
        count = 0
        def dfs(idx: int) -> None:
            nonlocal count
            if idx == 3:
                if temp[-1] % 2 == 0 and temp[0] != 0 and tuple(temp) not in ss:
                    ss.add(tuple(temp))
                    count += 1
                return
            
            for i in range(n):
                if i not in s:
                    temp.append(digits[i])
                    s.add(i)
                    dfs(idx + 1)
                    s.remove(i)
                    temp.pop()
        
        dfs(0)
        return count