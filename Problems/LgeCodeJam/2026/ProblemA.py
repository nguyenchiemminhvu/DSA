import sys
input = sys.stdin.readline

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n
        self.components = n

    def find(self, x):
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]
            x = self.parent[x]
        return x

    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if a == b:
            return False
        if self.size[a] < self.size[b]:
            a, b = b, a
        self.parent[b] = a
        self.size[a] += self.size[b]
        self.components -= 1
        return True

def solve():
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))

    if k >= n:
        print(-1)
        return

    order = sorted(range(n), key=lambda i: arr[i])

    dsu = DSU(n)
    active = [False] * n

    res = 0

    for i in order:
        active[i] = True

        # expand left
        j = i - k
        while j >= 0:
            if not active[j]:
                break
            if not dsu.union(i, j):
                break
            res += arr[i]
            j -= 1

        # expand right
        j = i + k
        while j < n:
            if not active[j]:
                break
            if not dsu.union(i, j):
                break
            res += arr[i]
            j += 1

    if dsu.components != 1:
        print(-1)
    else:
        print(res)

if __name__ == "__main__":
    solve()