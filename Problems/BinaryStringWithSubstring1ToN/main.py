# https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/

class Solution:
    def queryString(self, s: str, n: int) -> bool:
        max_binary_length = len(s)
        
        for i in range(1, min(n, 2**max_binary_length - 1) + 1):
            bin_str = bin(i)[2:]
            if bin_str not in s:
                return False
        
        return True

if __name__ == "__main__":
    s = "0110"
    n = 3
    solution = Solution()
    print(solution.queryString(s, n))  # Output: True

    s = "0110"
    n = 4
    solution = Solution()
    print(solution.queryString(s, n))  # Output: False