# https://leetcode.com/problems/sort-vowels-in-a-string/description

from collections import Counter

class Solution:
    def sortVowels(self, s: str) -> str:
        vowels = "AEIOUaeiou"
        is_vowel = set(vowels)
        counter = Counter([c for c in s if c in is_vowel])

        res = list(s)
        iv = 0
        for i, c in enumerate(res):
            if c in is_vowel:
                while iv <= len(vowels) and counter[vowels[iv]] <= 0:
                    iv += 1
                res[i] = vowels[iv]
                counter[vowels[iv]] -= 1
        return "".join(res)

if __name__ == "__main__":
    s = "lEetcOde"
    print(Solution().sortVowels(s))  # "lEOtcede"
    s = "lYmpH"
    print(Solution().sortVowels(s))  # "lYmpH"