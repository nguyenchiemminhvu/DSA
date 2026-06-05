from math import sqrt
import math
import random
from typing import List

class Solution:

    def __init__(self, radius: float, x_center: float, y_center: float):
        self.x = x_center
        self.y = y_center
        self.r = radius

    def randPoint(self) -> List[float]:
        r = self.r * sqrt(random.random())
        theta = 2 * math.pi * random.random()
        x = self.x + math.cos(theta) * r
        y = self.y + math.sin(theta) * r
        return [x, y]


# Your Solution object will be instantiated and called as such:
# obj = Solution(radius, x_center, y_center)
# param_1 = obj.randPoint()