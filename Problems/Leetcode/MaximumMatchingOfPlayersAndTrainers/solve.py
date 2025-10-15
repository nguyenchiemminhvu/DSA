from typing import List

class Solution:
    def matchPlayersAndTrainers(self, players: List[int], trainers: List[int]) -> int:
        players.sort()
        trainers.sort()
        ip = 0
        it = 0
        while ip < len(players) and it < len(trainers):
            if trainers[it] < players[ip]:
                it += 1
            else:
                it += 1
                ip += 1
        return ip