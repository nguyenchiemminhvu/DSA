## Problem

https://leetcode.com/problems/minimum-number-game/

```
You are given a 0-indexed integer array nums of even length and there is also an empty array arr. Alice and Bob decided to play a game where in every round Alice and Bob will do one move. The rules of the game are as follows:

Every round, first Alice will remove the minimum element from nums, and then Bob does the same.
Now, first Bob will append the removed element in the array arr, and then Alice does the same.
The game continues until nums becomes empty.
Return the resulting array arr.

Example 1:

Input: nums = [5,4,2,3]
Output: [3,2,5,4]
Explanation: In round one, first Alice removes 2 and then Bob removes 3. Then in arr firstly Bob appends 3 and then Alice appends 2. So arr = [3,2].
At the begining of round two, nums = [5,4]. Now, first Alice removes 4 and then Bob removes 5. Then both append in arr which becomes [3,2,5,4].

Example 2:

Input: nums = [2,5]
Output: [5,2]
Explanation: In round one, first Alice removes 2 and then Bob removes 5. Then in arr firstly Bob appends and then Alice appends. So arr = [5,2].

Constraints:

2 <= nums.length <= 100
1 <= nums[i] <= 100
nums.length % 2 == 0
```

## Observations

1. **Game Flow**: In each round:
   - Alice removes the minimum element from `nums`
   - Bob removes the next minimum element from `nums`
   - Bob appends his element to `arr` first
   - Alice appends her element to `arr` second

2. **Key Insight**: Since both players always pick the minimum available element, we can use a min-heap to efficiently get the smallest elements.

3. **Order Matters**: Even though Alice picks first, Bob appends first. This means in each pair of elements added to the result array, the second smallest element comes before the smallest element.

4. **Pattern Recognition**: If we sort the array `[a, b, c, d, e, f]`, the result will be `[b, a, d, c, f, e]` - we're essentially swapping adjacent pairs after sorting.

5. **Heap Usage**: Using a heap allows us to efficiently extract the minimum elements without having to sort the entire array at each step.

## Solution

1. **Heapify**: Convert the input array into a min-heap in O(n) time. This allows us to efficiently extract minimum elements.

2. **Game Simulation**: While there are elements in the heap:
   - Extract the minimum element (Alice's pick) - O(log n)
   - Extract the next minimum element (Bob's pick) - O(log n)
   - Append Bob's element first (as per game rules)
   - Append Alice's element second

3. **Time Complexity**: O(n log n)
   - Heapify: O(n)
   - Each pop operation: O(log n), done n times
   - Overall: O(n log n)

4. **Space Complexity**: O(1) extra space (not counting the output array)
   - We modify the input array in-place to create the heap
   - The result array is required by the problem

**Alternative Approach:**
You could also sort the array first and then swap adjacent pairs:
```python
def numberGame(self, nums: List[int]) -> List[int]:
    nums.sort()
    for i in range(0, len(nums), 2):
        nums[i], nums[i+1] = nums[i+1], nums[i]
    return nums
```
This has the same time complexity O(n log n) but might be slightly more intuitive.

## Tags

array, priority queue