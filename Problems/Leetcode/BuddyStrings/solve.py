class Solution:
    def buddyStrings(self, s: str, goal: str) -> bool:
        n = len(s)
        ng = len(goal)
        if n != ng:
            return False
        
        diff = []
        for i in range(n):
            if s[i] != goal[i]:
                diff.append(i)
        if len(diff) == 2:
            return s[diff[0]] == goal[diff[1]] and s[diff[1]] == goal[diff[0]]
        elif len(diff) == 0:
            if len(s) - len(list(set(s))) > 0:
                return True
        return False