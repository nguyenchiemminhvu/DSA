class Solution:
    def clumsy(self, n: int) -> int:
        # s = f"{n}"
        # op = ['*', '//', '+', '-']
        # io = 0
        # for val in range(n - 1, 0, -1):
        #     s += op[io] + f"{val}"
        #     io = (io + 1) % 4
        # return int(eval(s))

        st = [n]
        op = 0
        for val in range(n - 1, 0, -1):
            if op == 0:
                st[-1] *= val
            elif op == 1:
                st[-1] = int(st[-1] / val)
            elif op == 2:
                st.append(val)
            else:
                st.append(-val)
            op = (op + 1) % 4
        return sum(st)