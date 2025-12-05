# Valid Word

## Problem

https://leetcode.com/problems/valid-word/description/

A word is considered **valid** if it satisfies ALL of the following conditions:

1. It contains a **minimum of 3 characters**
2. It contains **only** digits (0-9) and English letters (uppercase and lowercase)
3. It includes **at least one vowel**
4. It includes **at least one consonant**

Given a string `word`, return `true` if the word is valid, otherwise return `false`.

**Notes:**
- Vowels are: 'a', 'e', 'i', 'o', 'u' and their uppercases ('A', 'E', 'I', 'O', 'U')
- A consonant is an English letter that is NOT a vowel

### Examples

**Example 1:**
```
Input: word = "234Adas"
Output: true
Explanation: This word satisfies all conditions:
- Length is 7 (≥ 3) ✓
- Contains only digits and letters ✓
- Has vowels: 'A', 'a' ✓
- Has consonants: 'd', 's' ✓
```

**Example 2:**
```
Input: word = "b3"
Output: false
Explanation: 
- Length is 2 (< 3) ✗
- Does not have a vowel ✗
```

**Example 3:**
```
Input: word = "a3$e"
Output: false
Explanation:
- Contains '$' which is not allowed ✗
- Does not have a consonant ✗
```

### Constraints
- `1 <= word.length <= 20`
- `word` consists of English uppercase and lowercase letters, digits, '@', '#', and '$'

## Observations

1. **Multiple validation checks required**: We need to validate 4 different conditions simultaneously
   
2. **Character classification**: Each character must be classified into one of:
   - Vowel (uppercase or lowercase)
   - Consonant (letter that's not a vowel)
   - Digit (0-9)
   - Invalid character (anything else like '@', '#', '$')

3. **Early termination opportunity**: If we find any invalid character, we can immediately return `false`

4. **Counting strategy**: We need to track:
   - Whether we've seen at least one vowel
   - Whether we've seen at least one consonant
   - We can use counters or boolean flags

5. **Edge cases to consider**:
   - Very short strings (< 3 characters)
   - Strings with only vowels (e.g., "aeiou")
   - Strings with only consonants (e.g., "bcd")
   - Strings with only digits (e.g., "123")
   - Strings with special characters mixed in

## Solution

### Approach: Single Pass Validation

The solution uses a **single pass** through the string to validate all conditions simultaneously.

### Algorithm Steps:

1. **Check minimum length**: 
   - If `len(word) < 3`, immediately return `false`

2. **Initialize counters**:
   - `count_vowel = 0`: tracks number of vowels found
   - `count_cons = 0`: tracks number of consonants found

3. **Iterate through each character**:
   - **Validate character type**: Check if character is a valid letter (uppercase/lowercase) or digit
     - If character is NOT in `string.ascii_lowercase`, `string.ascii_uppercase`, or `string.digits`, return `false`
   
   - **Classify and count**:
     - If character is a vowel ('AEIOUaeiou'), increment `count_vowel`
     - Else if character is NOT a digit, it must be a consonant, so increment `count_cons`
     - (Digits don't contribute to either vowel or consonant count)

4. **Final validation**:
   - Return `true` only if both `count_vowel > 0` AND `count_cons > 0`

### Why This Works

- **Single pass efficiency**: We only iterate through the string once
- **Early exit**: Invalid characters cause immediate return
- **Comprehensive validation**: All 4 conditions are checked
- **Clear separation**: Each condition is handled distinctly in the code

### Complexity Analysis

- **Time Complexity**: O(n)
  - Where n is the length of the word
  - We iterate through each character exactly once
  - Character lookups in strings and digit checks are O(1)

- **Space Complexity**: O(1)
  - We only use two integer counters
  - No additional data structures that scale with input size
  - `string.ascii_lowercase`, `string.ascii_uppercase`, and `string.digits` are constants

### Alternative Approaches

1. **Using boolean flags instead of counters**:
   ```python
   has_vowel = False
   has_consonant = False
   # Check and update flags during iteration
   ```
   - Slightly more memory efficient but essentially the same

2. **Using regular expressions**:
   ```python
   import re
   # Check length, valid chars, vowels, and consonants with regex
   ```
   - More concise but potentially less readable and slower

3. **Using sets for vowel checking**:
   ```python
   vowels = set('AEIOUaeiou')
   if c in vowels:  # O(1) lookup
   ```
   - Slightly faster for vowel checking due to set lookup

The current solution strikes a good balance between readability, efficiency, and simplicity.

# Tags

`#string` `#validation` `#single-pass`

