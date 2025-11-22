class Solution:
    def minimumRecolors(self, blocks: str, k: int) -> int:
        cur_black, cur_white = 0, 0
        l, r = 0, k - 1
        for i in range(l, r):
            cur_black += int(blocks[i] == 'B')
            cur_white += int(blocks[i] == 'W')
        
        n = len(blocks)
        min_white = n
        while r < n:
            cur_black += int(blocks[r] == 'B')
            cur_white += int(blocks[r] == 'W')
            min_white = min(min_white, cur_white)
            if blocks[l] == 'W':
                cur_white -= 1
            else:
                cur_black -= 1
            l += 1
            r += 1
        return min_white