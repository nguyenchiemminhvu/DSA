class Solution:
    def decodeCiphertext(self, s: str, rows: int) -> str:
        n = len(s)
        cols = n // rows
        mat = []
        for i in range(0, rows):
            mat.append(s[i * cols:i * cols + cols])
        for row in mat:
            print(row)
        
        res = []
        
        for start_col in range(cols):
            i, j = 0, start_col
            
            while i < rows and j < cols:
                res.append(mat[i][j])
                i += 1
                j += 1

        return ''.join(res).rstrip()