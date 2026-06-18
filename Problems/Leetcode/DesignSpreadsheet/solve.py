from collections import defaultdict

class Spreadsheet:

    def __init__(self, rows: int):
        self.mp = defaultdict(int)

    def setCell(self, cell: str, value: int) -> None:
        self.mp[cell] = value

    def resetCell(self, cell: str) -> None:
        self.mp[cell] = 0

    def getValue(self, formula: str) -> int:
        tokens = formula[1:].split('+')
        total_sum = 0
        
        for token in tokens:
            if token[0].isalpha():
                total_sum += self.mp[token]
            else:
                total_sum += int(token)
                
        return total_sum

# Your Spreadsheet object will be instantiated and called as such:
# obj = Spreadsheet(rows)
# obj.setCell(cell,value)
# obj.resetCell(cell)
# param_3 = obj.getValue(formula)