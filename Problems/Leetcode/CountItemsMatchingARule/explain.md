## Problem

https://leetcode.com/problems/count-items-matching-a-rule/

```
You are given an array items, where each items[i] = [typei, colori, namei] describes the type, color, and name of the ith item. You are also given a rule represented by two strings, ruleKey and ruleValue.

The ith item is said to match the rule if one of the following is true:

ruleKey == "type" and ruleValue == typei.
ruleKey == "color" and ruleValue == colori.
ruleKey == "name" and ruleValue == namei.
Return the number of items that match the given rule.

Example 1:

Input: items = [["phone","blue","pixel"],["computer","silver","lenovo"],["phone","gold","iphone"]], ruleKey = "color", ruleValue = "silver"
Output: 1
Explanation: There is only one item matching the given rule, which is ["computer","silver","lenovo"].

Example 2:

Input: items = [["phone","blue","pixel"],["computer","silver","phone"],["phone","gold","iphone"]], ruleKey = "type", ruleValue = "phone"
Output: 2
Explanation: There are only two items matching the given rule, which are ["phone","blue","pixel"] and ["phone","gold","iphone"]. Note that the item ["computer","silver","phone"] does not match.

Constraints:

1 <= items.length <= 104
1 <= typei.length, colori.length, namei.length, ruleValue.length <= 10
ruleKey is equal to either "type", "color", or "name".
All strings consist only of lowercase letters.
```

## Observations

1. **Problem Structure**: Each item is represented as a list/array with exactly 3 elements: `[type, color, name]` at indices 0, 1, and 2 respectively.

2. **Rule Matching**: We need to match the `ruleValue` against one specific attribute of each item based on the `ruleKey`:
   - If `ruleKey == "type"`, check index 0
   - If `ruleKey == "color"`, check index 1  
   - If `ruleKey == "name"`, check index 2

3. **Simple Counting**: We just need to count how many items have the matching attribute value.

4. **Direct Index Mapping**: The problem has a clear mapping from rule keys to array indices, making it efficient to determine which index to check.

## Solution

1. **Index Mapping**: Use a ternary operator to map the `ruleKey` to the corresponding index:
   - `"type"` → index 0
   - `"color"` → index 1
   - `"name"` → index 2 (default case)

2. **Iterate and Count**: Loop through each item in the `items` array and check if the value at the determined index matches the `ruleValue`.

3. **Clever Counting**: Use `int(item[idx] == ruleValue)` which converts the boolean result to an integer (1 if True, 0 if False), allowing us to accumulate the count directly.

**Time Complexity**: O(n) where n is the number of items, as we need to check each item once.

**Space Complexity**: O(1) as we only use a constant amount of extra space.

**Alternative Approaches:**
- Using a dictionary mapping: `{'type': 0, 'color': 1, 'name': 2}`
- Using `sum()` with a generator expression: `sum(1 for item in items if item[idx] == ruleValue)`

## Tags

- Array
- Hash Table
- String
- Simulation
- Easy

