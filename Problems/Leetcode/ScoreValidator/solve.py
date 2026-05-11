class Solution:
    def scoreValidator(self, events: list[str]) -> list[int]:
        s, c = 0, 0
        for e in events:
            if e.isdigit():
                s += int(e)
            elif e == 'W':
                c += 1
            else:
                s += 1
            
            if c == 10:
                break
        return [s, c]