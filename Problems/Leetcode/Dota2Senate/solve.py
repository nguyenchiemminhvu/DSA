from collections import deque

class Solution:
    def predictPartyVictory(self, senate: str) -> str:
        n = len(senate)
        radiant = deque()
        dire = deque()

        # Store indices
        for i, s in enumerate(senate):
            if s == 'R':
                radiant.append(i)
            else:
                dire.append(i)

        # Simulate rounds
        while radiant and dire:
            r = radiant.popleft()
            d = dire.popleft()

            if r < d:
                # Radiant bans Dire
                radiant.append(r + n)
            else:
                # Dire bans Radiant
                dire.append(d + n)

        return "Radiant" if radiant else "Dire"
