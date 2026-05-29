import sys
input = sys.stdin.readline

def solve():
    n = int(input())
    arr = list(map(int, input().split()))
    
    prefix_sum = [0] * (n + 1)
    for i in range(1, n + 1):
        prefix_sum[i] = prefix_sum[i - 1] + arr[i - 1]
    
    def sum_query(l: int, r: int) -> int:
        # 0-based indices
        return prefix_sum[r + 1] - prefix_sum[l]

    st = []
    left_greater = [-1] * n
    right_greater = [n] * n
    for i in range(n):
        while st and arr[st[-1]] <= arr[i]:
            right_greater[st[-1]] = i
            st.pop()
        if st:
            left_greater[i] = st[-1]
        st.append(i)
    
    res = float('-inf')

    # --------------------------------------------------------------
    # Brute force approach: for each position i, expand left and right to find max sum
    # => O(n^2) in worst case, TLE
    #
    # for i in range(n):
    #     # expand left
    #     cur = 0
    #     best_left = 0
    #     j = i - 1
    #     while j > left_greater[i]:
    #         cur += arr[j]
    #         best_left = max(best_left, cur)
    #         j -= 1
    #
    #     # expand right
    #     cur = 0
    #     best_right = 0
    #     j = i + 1
    #     while j < right_greater[i]:
    #         cur += arr[j]
    #         best_right = max(best_right, cur)
    #         j += 1
    #
    #     res = max(res, best_left + best_right)
    # --------------------------------------------------------------
    
    # --------------------------------------------------------------
    # Optimized approach: precompute max subarray sums for left and right expansions
    # => Faster in practices but still TLE due to O(n^2)
    # max_left = [0] * n  # max_left[i] = max subarray sum in (left_greater[i], i-1] ending at i-1
    # for i in range(n):
    #     left_bound = left_greater[i]
    #     min_pref = float('inf')
    #     for k in range(left_bound + 1, i + 1):
    #         min_pref = min(min_pref, prefix_sum[k])
    #
    #     max_left[i] = prefix_sum[i] - min_pref if i > left_bound + 1 else 0
    #
    # max_right = [0] * n  # max_right[i] = max subarray sum in [i+1, right_greater[i]-1] starting at i+1
    # for i in range(n):
    #     right_bound = right_greater[i]
    #     if i + 1 < right_bound:
    #         max_pref = float('-inf')
    #         for k in range(i + 1, right_bound):
    #             max_pref = max(max_pref, prefix_sum[k + 1])
    #         max_right[i] = max_pref - prefix_sum[i + 1]
    #     else:
    #         max_right[i] = 0
    #
    # res = float('-inf')
    # for i in range(n):
    #     res = max(res, max_left[i] + max_right[i])
    # --------------------------------------------------------------

    # --------------------------------------------------------------
    # segment tree for range min and max on prefix_sum
    class SegmentTree:
        def __init__(self, data):
            self.n = len(data)
            self.min_tree = [0] * (2 * self.n)
            self.max_tree = [0] * (2 * self.n)
            
            for i in range(self.n):
                self.min_tree[self.n + i] = data[i]
                self.max_tree[self.n + i] = data[i]
            
            for i in range(self.n - 1, 0, -1):
                self.min_tree[i] = min(self.min_tree[2 * i], self.min_tree[2 * i + 1])
                self.max_tree[i] = max(self.max_tree[2 * i], self.max_tree[2 * i + 1])

        def query_min(self, l, r):
            l += self.n
            r += self.n
            res = float('inf')
            while l <= r:
                if l & 1:
                    res = min(res, self.min_tree[l])
                    l += 1
                if not (r & 1):
                    res = min(res, self.min_tree[r])
                    r -= 1
                l >>= 1
                r >>= 1
            return res

        def query_max(self, l, r):
            l += self.n
            r += self.n
            res = float('-inf')
            while l <= r:
                if l & 1:
                    res = max(res, self.max_tree[l])
                    l += 1
                if not (r & 1):
                    res = max(res, self.max_tree[r])
                    r -= 1
                l >>= 1
                r >>= 1
            return res
    
    segment_tree = SegmentTree(prefix_sum)
    for i in range(n):
        left_bound = left_greater[i] + 1
        right_bound = right_greater[i]
        
        best_left = 0
        if left_bound <= i:
            min_prefix_left = segment_tree.query_min(left_bound, i)
            best_left = max(0, prefix_sum[i] - min_prefix_left)

        best_right = 0
        if i + 1 <= right_bound - 1:
            max_prefix_right = segment_tree.query_max(i + 1, right_bound - 1)
            best_right = max(0, max_prefix_right - prefix_sum[i + 1])
        
        res = max(res, best_left + best_right)
    # --------------------------------------------------------------

    print(res)

def main():
    solve()

if __name__ == "__main__":
    main()