## Problem

https://leetcode.com/problems/reduce-array-size-to-the-half/

```
You are given an integer array arr. You can choose a set of integers and remove all the occurrences of these integers in the array.

Return the minimum size of the set so that at least half of the integers of the array are removed.

Example 1:

Input: arr = [3,3,3,3,5,5,5,2,2,7]
Output: 2
Explanation: Choosing {3,7} will make the new array [5,5,5,2,2] which has size 5 (i.e equal to half of the size of the old array).
Possible sets of size 2 are {3,5},{3,2},{5,2}.
Choosing set {2,7} is not possible as it will make the new array [3,3,3,3,5,5,5] which has a size greater than half of the size of the old array.

Example 2:

Input: arr = [7,7,7,7,7,7]
Output: 1
Explanation: The only possible set you can choose is {7}. This will make the new array empty.

Constraints:

2 <= arr.length <= 105
arr.length is even.
1 <= arr[i] <= 105
```

## Observations

1. **Goal**: Find the minimum number of distinct integers to remove such that at least half of the array elements are removed.

2. **Key Insight**: To minimize the number of distinct integers in our set, we should prioritize removing integers that appear most frequently in the array.

3. **Greedy Approach**: Sort integers by their frequency in descending order, then keep removing the most frequent ones until we've removed at least half of the array.

4. **Array Length**: The constraint guarantees that `arr.length` is even, so `arr.length // 2` gives us exactly half.

5. **Frequency Counting**: We need to count the frequency of each element first, then make decisions based on these frequencies.

## Solution

The solution uses a **greedy algorithm** with the following steps:

### Algorithm Steps:

1. **Count Frequencies**: Build a frequency map `f` where `f[val]` represents how many times `val` appears in the array.

2. **Sort by Frequency**: Create a list of keys (distinct values) sorted by their frequencies in descending order. The most frequent elements come first.

3. **Greedy Selection**: Starting from the most frequent element, keep removing elements until we've removed at least half of the original array size.

4. **Track Progress**: Use `count` to track how many distinct integers we've chosen, and `n` to track remaining array size.

### Example Trace:

For `arr = [3,3,3,3,5,5,5,2,2,7]`:

1. **Frequencies**: `{3: 4, 5: 3, 2: 2, 7: 1}`
2. **Sorted keys**: `[3, 5, 2, 7]` (by frequency: 4, 3, 2, 1)
3. **Target**: Remove at least `10 // 2 = 5` elements
4. **Process**:
   - Remove all 3's: `n = 10 - 4 = 6`, `count = 1`
   - Still `6 > 5`, so remove all 5's: `n = 6 - 3 = 3`, `count = 2`
   - Now `3 ≤ 5`, so we stop
5. **Result**: `count = 2`

### Time Complexity: 
- **O(n log k)** where n is array length and k is number of distinct elements
- Frequency counting: O(n)
- Sorting: O(k log k) 
- Greedy selection: O(k)

### Space Complexity: 
- **O(k)** for the frequency map and sorted keys list

## Tags

array, hash table, greedy