import re

class Solution:
    def reformatNumber(self, number: str) -> str:
        number = "".join(re.split(r"[\s-]+", number))
        number = [number[i:i+3] for i in range(0, len(number), 3)]
        if len(number) > 1 and len(number[-2]) + len(number[-1]) == 4:
            number[-1] = number[-2][-1] + number[-1]
            number[-2] = number[-2][:-1]
        return "-".join(number)