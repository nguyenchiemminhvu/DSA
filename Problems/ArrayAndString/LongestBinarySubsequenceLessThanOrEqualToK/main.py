# https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/

class Solution:
    def right_most_bit(self, val: int):
        if (val == 0):
            return 0
        pos = 0
        while (val > 0):
            val >>= 1
            pos += 1
        return pos
    
    def longestSubsequence(self, s: str, k: int) -> int:
        res = 0
        s = s[::-1]
        right_most = self.right_most_bit(k)
        total = 0
        for i in range(0, len(s)):
            if (s[i] == '0'):
                res += 1
            else:
                if (i <= right_most and total + (1 << i) <= k):
                    res += 1
                    total += (1 << i)

        return res

if __name__ == "__main__":
    s = "1001010"
    k = 5
    print(Solution().longestSubsequence(s, k))  # Output: 5

    s = "0010101"
    k = 5
    print(Solution().longestSubsequence(s, k))  # Output: 6

    s = "1111"
    k = 1
    print(Solution().longestSubsequence(s, k))  # Output: 1