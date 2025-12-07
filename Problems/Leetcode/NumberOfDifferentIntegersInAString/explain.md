## Problem

https://leetcode.com/problems/number-of-different-integers-in-a-string/

```
You are given a string word that consists of digits and lowercase English letters.

You will replace every non-digit character with a space. For example, "a123bc34d8ef34" 
will become " 123  34 8  34". Notice that you are left with some integers that are 
separated by at least one space: "123", "34", "8", and "34".

Return the number of different integers after performing the replacement operations on word.

Two integers are considered different if their decimal representations without any leading 
zeros are different.

Example 1:
Input: word = "a123bc34d8ef34"
Output: 3
Explanation: The three different integers are "123", "34", and "8". Notice that "34" is 
only counted once.

Example 2:
Input: word = "leet1234code234"
Output: 2

Example 3:
Input: word = "a1b01c001"
Output: 1
Explanation: The three integers "1", "01", and "001" all represent the same integer because
the leading zeros are ignored when comparing their decimal values.

Constraints:
- 1 <= word.length <= 1000
- word consists of digits and lowercase English letters.
```

## Observations

1. **Character Replacement**: We need to replace all non-digit characters with spaces to isolate the numeric segments.

2. **Leading Zeros**: The key challenge is handling leading zeros. Numbers like "01", "001", and "1" should all be treated as the same integer (1).

3. **Uniqueness**: We need to count only unique integers, so duplicates should be counted once.

4. **Edge Cases**:
   - Consecutive non-digit characters create multiple spaces
   - Numbers with leading zeros must be normalized
   - Empty strings after splitting should be ignored
   - Single digit numbers

5. **Approach**: 
   - Replace non-digits with spaces
   - Split the string to extract number segments
   - Convert to integers (automatically removes leading zeros)
   - Use a set to track unique values

## Solution

```python
class Solution:
    def numDifferentIntegers(self, word: str) -> int:
        return len(set(list(map(int, "".join([' ' if not w.isdigit() else w for w in word]).split()))))
```

**Explanation:**

This one-liner solution performs the following steps:

1. **`[' ' if not w.isdigit() else w for w in word]`**: 
   - List comprehension that iterates through each character in `word`
   - Replaces non-digit characters with spaces
   - Keeps digit characters as-is

2. **`"".join(...)`**: 
   - Joins the list of characters back into a string
   - Example: "a123bc34" becomes " 123  34"

3. **`.split()`**: 
   - Splits the string by whitespace
   - Automatically handles multiple consecutive spaces
   - Returns list of numeric strings: ["123", "34"]

4. **`map(int, ...)`**: 
   - Converts each string to an integer
   - Automatically removes leading zeros (e.g., "001" → 1)
   - Returns an iterator of integers

5. **`set(list(...))`**: 
   - Converts the map iterator to a list, then to a set
   - Eliminates duplicate integers
   - Example: [123, 34, 8, 34] → {123, 34, 8}

6. **`len(...)`**: 
   - Returns the count of unique integers

**Time Complexity**: O(n) where n is the length of the word
- Iterating through the string: O(n)
- Splitting: O(n)
- Converting to integers: O(k) where k is the number of numeric segments
- Set operations: O(k)

**Space Complexity**: O(n) for the intermediate string and O(k) for the set of unique integers

**Alternative Readable Solution:**

```python
class Solution:
    def numDifferentIntegers(self, word: str) -> int:
        # Replace non-digits with spaces
        for char in word:
            if not char.isdigit():
                word = word.replace(char, ' ')
        
        # Split and convert to integers (removes leading zeros)
        numbers = word.split()
        unique_integers = set()
        
        for num_str in numbers:
            unique_integers.add(int(num_str))
        
        return len(unique_integers)
```

This alternative is more verbose but easier to understand for those less familiar with functional programming constructs.

# Tags

