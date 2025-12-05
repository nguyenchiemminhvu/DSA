class Solution:
    def canAliceWin(self, n: int) -> bool:
        k = 10
        alice_turn = True
        while n - k >= 0:
            n -= k
            k -= 1
            alice_turn = not alice_turn

        return False if alice_turn else True