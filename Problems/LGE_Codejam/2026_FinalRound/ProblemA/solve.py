import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))
    
    for _ in range(T):
        N = int(next(iterator))
        K = int(next(iterator))
        A = [int(next(iterator)) for _ in range(N)]
        
        res = float('inf')
        
        # Try every possible B[0] in (A[0] + [0 - K])
        for k in range(K):
            B = []
            B.append(A[0] + k)
            min_op = k
            for i in range(1, N):
                prev_mod = B[-1] % K
                if A[i] <= B[-1]:
                    diff = B[-1] - A[i] + 1
                    min_op += diff
                    B.append(A[i] + diff)
                else:
                    cur_mod = A[i] % K
                    if cur_mod <= prev_mod:
                        diff = (prev_mod - cur_mod + 1) % K
                        min_op += diff
                        B.append(A[i] + diff)
                    else:
                        diff = (K - cur_mod + prev_mod + 1) % K
                        min_op += diff
                        B.append(A[i] + diff)
            res = min(res, min_op)
        
        print(res)

if __name__ == '__main__':
    solve()
