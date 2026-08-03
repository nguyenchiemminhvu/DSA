class Solution:
    def winnerSquareGame(self, n: int) -> bool:
        def list_squares(n: int) -> list[int]:
            squares = []
            i = 1
            while i * i <= n:
                squares.append(i * i)
                i += 1
            return squares
        
        squares = list_squares(n)

        from functools import lru_cache
        @lru_cache(None)
        def F(remain: int, a_turn: bool) -> bool:
            if remain == 0:
                return not a_turn
            
            if a_turn:
                for val in squares:
                    if val > remain:
                        break
                    if F(remain - val, False):
                        return True
                return False
            else:
                for val in squares:
                    if val > remain:
                        break
                    if not F(remain - val, True):
                        return False
                return True
        
        return F(n, True)