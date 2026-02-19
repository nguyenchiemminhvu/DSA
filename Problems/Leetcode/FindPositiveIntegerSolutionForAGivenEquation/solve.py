from typing import List

"""
   This is the custom function interface.
   You should not implement it, or speculate about its implementation
   class CustomFunction:
       # Returns f(x, y) for any given positive integers x and y.
       # Note that f(x, y) is increasing with respect to both x and y.
       # i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
       def f(self, x, y):
  
"""

class Solution:
    def findSolution(self, custom: 'CustomFunction', z: int) -> List[List[int]]:
        res = []
        x = 1
        y = 1000
        while x <= 1000 and y >= 1:
            value = custom.f(x, y)
            if value == z:
                res.append([x, y])
                x += 1
                y -= 1
            else:
                if value < z:
                    x += 1
                else:
                    y -= 1
        return res