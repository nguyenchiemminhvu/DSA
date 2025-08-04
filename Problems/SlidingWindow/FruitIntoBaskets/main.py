# https://leetcode.com/problems/fruit-into-baskets/description

from collections import defaultdict
class Solution:
    def totalFruit(self, fruits: List[int]) -> int:
        n = len(fruits)
        left = 0
        right = 0
        res = 0
        freq = defaultdict(int)
        while (right < n):
            freq[fruits[right]] += 1
            while (len(freq) > 2):
                freq[fruits[left]] -= 1
                if (freq[fruits[left]] <= 0):
                    freq.pop(fruits[left])
                left += 1
            total = 0
            for k, v in freq.items():
                total += v
            res = max(res, total)
            right += 1
        return res

if __name__ == "__main__":
    fruits = [1, 2, 1]
    print(Solution().totalFruit(fruits))  # Output: 3
    fruits = [0, 1, 2, 2]
    print(Solution().totalFruit(fruits))  # Output: 3
    fruits = [1, 2, 3, 2, 2]
    print(Solution().totalFruit(fruits))  # Output: 4