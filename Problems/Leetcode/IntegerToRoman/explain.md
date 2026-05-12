## Problem

https://leetcode.com/problems/integer-to-roman/description/

Convert an integer to its Roman numeral representation.

Seven symbols represent Roman numerals:
- I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000

**Rules:**
1. If the value doesn't start with 4 or 9, select the maximal symbol that can be subtracted, append it, and recursively convert the remainder.
2. If the value starts with 4 or 9, use subtractive forms: IV (4), IX (9), XL (40), XC (90), CD (400), CM (900).
3. Only powers of 10 (I, X, C, M) can appear consecutively up to 3 times. V, L, D cannot repeat.

**Constraints:** $1 \leq \text{num} \leq 3999$

**Examples:**
- Input: 3749 → Output: "MMMDCCXLIX"
- Input: 58 → Output: "LVIII"
- Input: 1994 → Output: "MCMXCIV"

## Observations

1. **Greedy Approach is Optimal**: Since we're converting from largest to smallest values, we can use a greedy strategy. At each step, we subtract the largest possible value that doesn't exceed the remaining number.

2. **Include Subtractive Forms in Mapping**: Rather than handling subtractive forms separately (4, 9, 40, 90, 400, 900), we can include them directly in our value-to-symbol mapping. This simplifies the logic significantly.

3. **Order Matters**: We need to process values in descending order (1000 down to 1). By iterating through our mapping in reverse, we ensure we always take the largest applicable value first.

4. **Repeated Subtraction**: Since the same value might apply multiple times (e.g., 3000 = M + M + M), we use a while loop to handle consecutive occurrences before moving to the next smaller value.

5. **Dictionary Preserves Insertion Order**: In Python 3.7+, dictionaries maintain insertion order, which makes reverse iteration straightforward.

## Solution

**Approach: Greedy with Value-Symbol Mapping**

The key insight is to create a mapping of all relevant values (including subtractive forms) to their Roman symbols in descending order. Then, we greedily subtract the largest value at each step:

```python
class Solution:
    def intToRoman(self, num: int) -> str:
        d: Dict[str, int] = {}
        d['I'] = 1
        d['IV'] = 4
        d['V'] = 5
        d['IX'] = 9
        d['X'] = 10
        d['XL'] = 40
        d['L'] = 50
        d['XC'] = 90
        d['C'] = 100
        d['CD'] = 400
        d['D'] = 500
        d['CM'] = 900
        d['M'] = 1000

        res = ""
        for roman, value in reversed(d.items()):
            while num >= value:
                num -= value
                res += roman
        return res
```

**Step-by-Step Walkthrough (Example: num = 1994)**

1. Start with num = 1994, res = ""
2. Process M (1000): 1994 ≥ 1000 → res = "M", num = 994
3. Skip D, C (994 < 500 and 994 < 100)
4. Process CM (900): 994 ≥ 900 → res = "MCM", num = 94
5. Process XC (90): 94 ≥ 90 → res = "MCMXC", num = 4
6. Process IV (4): 4 ≥ 4 → res = "MCMXCIV", num = 0
7. Return "MCMXCIV"

**Complexity Analysis:**
- **Time Complexity**: O(1) - We iterate through at most 13 symbol-value pairs, and for each number, we process at most 3 consecutive symbols. Since num ≤ 3999, the total operations are bounded.
- **Space Complexity**: O(1) - The dictionary has a fixed size (13 entries), and the result string length is at most ~4 characters per thousand, so bounded by the constraint.

**Alternative Approaches:**

1. **Array-based Approach** (more explicit):
   ```python
   values = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
   symbols = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"]
   
   res = ""
   for value, symbol in zip(values, symbols):
       while num >= value:
           res += symbol
           num -= value
   return res
   ```

2. **List of Tuples** (most readable):
   ```python
   pairs = [
       (1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'),
       (100, 'C'), (90, 'XC'), (50, 'L'), (40, 'XL'),
       (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'), (1, 'I')
   ]
   
   res = ""
   for value, symbol in pairs:
       while num >= value:
           res += symbol
           num -= value
   return res
   ```

# Tags

- Greedy Algorithm
- String Building
- Roman Numerals
- Hash Map / Dictionary

