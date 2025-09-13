# https://leetcode.com/problems/find-most-frequent-vowel-and-consonant

class Solution:
    def maxFreqSum(self, s: str) -> int:
        vowels = 'aeiou'

        freq = [0] * 128
        for c in s:
            freq[ord(c)] += 1
        
        max_v = 0
        max_c = 0
        for i in range(ord('a'), ord('z') + 1):
            if chr(i) in vowels:
                max_v = max(max_v, freq[i])
            else:
                max_c = max(max_c, freq[i])
        return max_v + max_c

if __name__ == "__main__":
    s = Solution()
    print(s.maxFreqSum("leetcode"))
    print(s.maxFreqSum("abbcccdddd"))
    print(s.maxFreqSum("aeiou"))