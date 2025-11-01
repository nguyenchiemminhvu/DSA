from typing import List

class Solution:
    def countMatches(self, items: List[List[str]], ruleKey: str, ruleValue: str) -> int:
        count = 0
        idx = 0 if ruleKey == 'type' else 1 if ruleKey == 'color' else 2
        for item in items:
            count += int(item[idx] == ruleValue)
        return count