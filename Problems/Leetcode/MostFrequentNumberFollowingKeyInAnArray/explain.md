## Problem

https://leetcode.com/problems/most-frequent-number-following-key-in-an-array/description/

```
You are given a 0-indexed integer array nums. You are also given an integer key, which is present in nums.

For every unique integer target in nums, count the number of times target immediately follows an occurrence of key in nums. In other words, count the number of indices i such that:

0 <= i <= nums.length - 2,
nums[i] == key and,
nums[i + 1] == target.
Return the target with the maximum count. The test cases will be generated such that the target with maximum count is unique.

Example 1:

Input: nums = [1,100,200,1,100], key = 1
Output: 100
Explanation: For target = 100, there are 2 occurrences at indices 1 and 4 which follow an occurrence of key.
No other integers follow an occurrence of key, so we return 100.

Example 2:

Input: nums = [2,2,2,2,3], key = 2
Output: 2
Explanation: For target = 2, there are 3 occurrences at indices 1, 2, and 3 which follow an occurrence of key.
For target = 3, there is only one occurrence at index 4 which follows an occurrence of key.
target = 2 has the maximum number of occurrences following an occurrence of key, so we return 2.

Constraints:

2 <= nums.length <= 1000
1 <= nums[i] <= 1000
The test cases will be generated such that the answer is unique.
```

## Observations

1. **Problem Understanding**: We need to find the number that appears most frequently immediately after occurrences of a given `key` in the array.

2. **Key Insights**:
   - We only care about positions where `nums[i] == key` and look at `nums[i+1]`
   - We need to count frequencies of numbers that follow the key
   - The result is guaranteed to be unique (as per problem constraints)

3. **Edge Cases**:
   - Key appears at the last position (no following number) - handled by `range(1, len(nums))`
   - Multiple numbers with same frequency - problem states answer is unique
   - Array length is at least 2 (per constraints)

4. **Algorithm Approach**:
   - Use a hash map (defaultdict) to count frequencies
   - Single pass through the array starting from index 1
   - Track the maximum frequency and return corresponding number

## Solution

**Algorithm**: Hash Map + Frequency Counting

**Time Complexity**: O(n) where n is the length of the array
- Single pass to count frequencies: O(n)
- Finding max frequency: O(k) where k is number of unique followers
- Finding the key with max frequency: O(k)
- Overall: O(n + k) = O(n) since k ≤ n

**Space Complexity**: O(k) where k is the number of unique numbers following the key
- In worst case, k could be n-1, so O(n) space

**Step-by-step breakdown**:

1. **Initialize frequency map**: `f = defaultdict(int)` creates a hash map with default value 0
2. **Count frequencies**: Loop through array from index 1 to end
   - Check if previous element equals key: `nums[i-1] == key`
   - If yes, increment count for current element: `f[nums[i]] += 1`
3. **Find maximum frequency**: `target_f = max(f.values())`
4. **Return the number with max frequency**: Iterate through frequency map to find key with maximum value

**Example walkthrough**:
```
nums = [1,100,200,1,100], key = 1

i=1: nums[0]=1 == key, so f[100] = 1
i=2: nums[1]=100 != key, skip
i=3: nums[2]=200 != key, skip  
i=4: nums[3]=1 == key, so f[100] = 2

f = {100: 2}
max frequency = 2
return 100
```

# Tags

- **Data Structures**: Hash Map, Array
- **Algorithms**: Frequency Counting, Linear Scan
- **Patterns**: Counting Pattern, Key-Value Mapping
- **Difficulty**: Easy
- **Time**: O(n)
- **Space**: O(n)

