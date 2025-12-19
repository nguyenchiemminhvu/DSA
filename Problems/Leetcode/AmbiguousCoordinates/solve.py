from typing import List

class Solution:
    def ambiguousCoordinates(self, s: str) -> List[str]:
        digits = s[1:-1]  # remove '(' and ')'
        n = len(digits)
        result = []

        # DFS to generate all valid numbers from a substring
        def dfs(num: str) -> List[str]:
            res = []

            # Case 1: number without decimal
            if num == "0" or not num.startswith("0"):
                res.append(num)

            # Case 2: numbers with decimal
            for i in range(1, len(num)):
                left = num[:i]
                right = num[i:]

                # Left part cannot have leading zeros unless it's exactly "0"
                if left.startswith("0") and left != "0":
                    continue

                # Right part cannot end with zero
                if right.endswith("0"):
                    continue

                res.append(left + "." + right)

            return res

        # Split digits into left and right parts
        for i in range(1, n):
            left_part = digits[:i]
            right_part = digits[i:]

            left_numbers = dfs(left_part)
            right_numbers = dfs(right_part)

            for l in left_numbers:
                for r in right_numbers:
                    result.append(f"({l}, {r})")

        return result
