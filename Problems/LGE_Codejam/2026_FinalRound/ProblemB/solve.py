import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    
    L = int(next(iterator))
    N = int(next(iterator))
    K = int(next(iterator))
    
    A = [int(next(iterator)) for _ in range(N)]
    
    min_dist = float('inf')
    for i in range(N):
        if i >= K - 1:
            min_dist = min(min_dist, A[i] - A[i - K + 1])
    
    print(min_dist)

if __name__ == '__main__':
    solve()
