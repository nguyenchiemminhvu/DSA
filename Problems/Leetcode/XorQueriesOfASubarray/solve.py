class Solution:
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        n = len(arr)

        # => got TLE
        # res = []
        # for left, right in queries:
        #     x = 0
        #     for i in range(left, right + 1):
        #         x ^= arr[i]
        #     res.append(x)
        # return res

        # => got MLE
        # mp = defaultdict(lambda: defaultdict(int))
        # for i in range(n):
        #     x = 0
        #     for j in range(i, n):
        #         x ^= arr[j]
        #         mp[i][j] = x
        # res = []
        # for left, right in queries:
        #     res.append(mp[left][right])
        # return res

        prefix_xor = [0] * (n + 1)
        for i in range(n):
            prefix_xor[i + 1] = prefix_xor[i] ^ arr[i]
        
        res = []
        for left, right in queries:
            x = prefix_xor[right + 1] ^ prefix_xor[left]
            res.append(x)
        return res