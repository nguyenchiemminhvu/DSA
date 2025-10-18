class Solution:
    def maximumSwap(self, num: int) -> int:
        s = list(str(num))
        n = len(s)
        left = 0
        while left < n:
            s_right = s[left:]
            reverse_s_right = s_right[::-1]
            max_idx = len(s_right) - 1 - reverse_s_right.index(max(s_right))
            if max_idx > 0 and s_right[0] != s_right[max_idx]:
                s_right[0], s_right[max_idx] = s_right[max_idx], s_right[0]
                s = s[:left] + s_right
                break
            left += 1

        return int("".join(s))