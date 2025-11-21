import string

class Solution:
    def countPalindromicSubsequence(self, s: str) -> int:
        count = 0
        prefix = [[-1, -1] for _ in range(26)]
        for i, c in enumerate(s):
            ip = ord(c) - ord('a')
            if prefix[ip][0] == -1:
                prefix[ip][0] = i
            else:
                prefix[ip][1] = i
        for c in string.ascii_lowercase:
            ip = ord(c) - ord('a')
            left, right = prefix[ip]
            if left < right:
                count += len(set(list(s[left + 1:right])))
        return count