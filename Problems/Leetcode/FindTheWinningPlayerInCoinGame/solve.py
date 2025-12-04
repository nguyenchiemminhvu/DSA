class Solution:
    def winningPlayer(self, x: int, y: int) -> str:
        alice_turn = True
        while x and y:
            if x < 1 or y < 4:
                break
            x -= 1
            y -= 4
            alice_turn = not alice_turn
        
        return "Bob" if alice_turn else "Alice"