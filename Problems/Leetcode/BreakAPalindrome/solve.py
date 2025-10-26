class Solution:
    def breakPalindrome(self, palindrome: str) -> str:
        n = len(palindrome)
        if n == 1:
            return ""

        s = list(palindrome)
        if all(c == 'a' for c in s):
            s[-1] = 'b'
        else:
            left = 0
            right = n - 1
            found = False
            while left < right:
                if s[left] != 'a':
                    s[left] = 'a'
                    found = True
                    break
                left += 1
                right -= 1
            if not found:
                s[-1] = 'b'

        return "".join(s)