## Problem

https://leetcode.com/problems/coupon-code-validator/description/

```
You are given three arrays of length n that describe the properties of n coupons: code, businessLine, and isActive. The ith coupon has:

- code[i]: a string representing the coupon identifier.
- businessLine[i]: a string denoting the business category of the coupon.
- isActive[i]: a boolean indicating whether the coupon is currently active.

A coupon is considered valid if all of the following conditions hold:
1. code[i] is non-empty and consists only of alphanumeric characters (a-z, A-Z, 0-9) and underscores (_).
2. businessLine[i] is one of the following four categories: "electronics", "grocery", "pharmacy", "restaurant".
3. isActive[i] is true.

Return an array of the codes of all valid coupons, sorted first by their businessLine in the order: 
"electronics", "grocery", "pharmacy", "restaurant", and then by code in lexicographical (ascending) order 
within each category.

Example 1:
Input: code = ["SAVE20","","PHARMA5","SAVE@20"], 
       businessLine = ["restaurant","grocery","pharmacy","restaurant"], 
       isActive = [true,true,true,true]
Output: ["PHARMA5","SAVE20"]

Explanation:
- First coupon is valid.
- Second coupon has empty code (invalid).
- Third coupon is valid.
- Fourth coupon has special character @ (invalid).

Example 2:
Input: code = ["GROCERY15","ELECTRONICS_50","DISCOUNT10"], 
       businessLine = ["grocery","electronics","invalid"], 
       isActive = [false,true,true]
Output: ["ELECTRONICS_50"]

Explanation:
- First coupon is inactive (invalid).
- Second coupon is valid.
- Third coupon has invalid business line (invalid).

Constraints:
- n == code.length == businessLine.length == isActive.length
- 1 <= n <= 100
- 0 <= code[i].length, businessLine[i].length <= 100
- code[i] and businessLine[i] consist of printable ASCII characters.
- isActive[i] is either true or false.
```

## Observations

1. **Validation Requirements**: Each coupon must pass three validation checks:
   - The coupon code must be non-empty and contain only valid characters (alphanumeric + underscore)
   - The business line must be one of exactly four predefined categories
   - The coupon must be active (isActive = true)

2. **Character Validation**: For the code validation, we need to check if all characters are in the set:
   - Lowercase letters: a-z
   - Uppercase letters: A-Z
   - Digits: 0-9
   - Underscore: _

3. **Two-Level Sorting**:
   - Primary sort: by business line in a specific order (electronics → grocery → pharmacy → restaurant)
   - Secondary sort: by code lexicographically within each business line category

4. **Data Structure Choice**: Using a dictionary/map to group valid coupon codes by business line allows us to:
   - Efficiently collect codes for each category
   - Sort codes within each category independently
   - Iterate through categories in the required order

5. **Edge Cases to Handle**:
   - Empty code strings
   - Special characters in code (like @, #, -, etc.)
   - Invalid business line categories
   - Inactive coupons
   - Multiple valid coupons in the same category

## Solution

1. **Initialization**:
   - Define the valid business lines in the required output order
   - Create a string containing all valid characters for coupon codes
   - Initialize a dictionary to group codes by business line

2. **Validation and Grouping** (O(n × m) where m is average code length):
   - For each coupon at index i:
     - Check if `isActive[i]` is true AND `businessLine[i]` is valid
     - Verify the code is non-empty
     - Validate all characters in the code using `all(c in words for c in code[i])`
     - If all conditions pass, add the code to the dictionary under its business line

3. **Sorting and Building Result** (O(k log k) where k is number of valid coupons per category):
   - Iterate through business lines in the predefined order
   - For each business line that has valid coupons:
     - Sort the codes lexicographically
     - Extend the result array with the sorted codes

**Time Complexity**: O(n × m + k log k)
- n = number of coupons
- m = average length of coupon codes
- k = number of valid coupons (in worst case, could be n)

**Space Complexity**: O(k)
- Dictionary to store valid coupon codes
- Result array

**Key Techniques**:
- Using `string.ascii_lowercase`, `string.ascii_uppercase`, and `string.digits` for character validation
- Dictionary for grouping by category
- Two-level sorting by iterating in predefined order and using built-in sort

# Tags
#array #string #sorting #hashtable #validation #filtering

