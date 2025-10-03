## Problem Description

https://leetcode.com/problems/minimum-index-sum-of-two-lists/

```
Given two arrays of strings list1 and list2, find the common strings with the least index sum.

A common string is a string that appeared in both list1 and list2.

A common string with the least index sum is a common string such that if it appeared at list1[i] and list2[j] then i + j should be the minimum value among all the other common strings.

Return all the common strings with the least index sum. Return the answer in any order.

Example 1:

Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
Output: ["Shogun"]
Explanation: The only common string is "Shogun".

Example 2:

Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["KFC","Shogun","Burger King"]
Output: ["Shogun"]
Explanation: The common string with the least index sum is "Shogun" with index sum = (0 + 1) = 1.

Example 3:

Input: list1 = ["happy","sad","good"], list2 = ["sad","happy","good"]
Output: ["sad","happy"]
Explanation: There are three common strings:
"happy" with index sum = (0 + 1) = 1.
"sad" with index sum = (1 + 0) = 1.
"good" with index sum = (2 + 2) = 4.
The strings with the least index sum are "sad" and "happy".

Constraints:

1 <= list1.length, list2.length <= 1000
1 <= list1[i].length, list2[i].length <= 30
list1[i] and list2[i] consist of spaces ' ' and English letters.
All the strings of list1 are unique.
All the strings of list2 are unique.
There is at least a common string between list1 and list2.
```

## Observations

1. **Problem Requirements**: Find all common strings between two lists that have the minimum index sum.
2. **Index Sum**: For a common string appearing at `list1[i]` and `list2[j]`, the index sum is `i + j`.
3. **Multiple Results**: There can be multiple strings with the same minimum index sum.
4. **Hash Map Approach**: We can use hash maps to store the index of each string in both lists for O(1) lookup.
5. **Two-Pass Strategy**: 
   - First pass: Build hash maps for both lists to store string → index mappings
   - Second pass: Iterate through one list and check for common strings, tracking minimum sum

## Solution

**Algorithm:**
1. Create two hash maps (`m1`, `m2`) to store the index of each string in `list1` and `list2` respectively
2. Populate both hash maps by iterating through the lists
3. Initialize `min_sum` to a large value and an empty result list
4. Iterate through `list1` and for each string:
   - Check if it exists in `list2` (using `m2`)
   - Calculate the index sum: `m1[string] + m2[string]`
   - If the sum is smaller than current `min_sum`, update `min_sum` and reset result list
   - If the sum equals `min_sum`, add the string to result list
5. Return the result list

**Time Complexity:** O(n + m) where n and m are the lengths of list1 and list2
**Space Complexity:** O(n + m) for the hash maps

## Tags

array, string, hash table