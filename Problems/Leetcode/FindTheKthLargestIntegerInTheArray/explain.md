## Problem

https://leetcode.com/problems/find-the-kth-largest-integer-in-the-array/description/

You are given an array of strings `nums` and an integer `k`. Each string in `nums` represents an integer without leading zeros.

Return the string that represents the **kth largest** integer in `nums`.

**Note:** Duplicate numbers should be counted distinctly. For example, if `nums` is `["1","2","2"]`, `"2"` is the first largest integer, `"2"` is the second-largest integer, and `"1"` is the third-largest integer.

**Example 1:**
```
Input: nums = ["3","6","7","10"], k = 4
Output: "3"
Explanation: The numbers sorted in non-decreasing order are ["3","6","7","10"].
The 4th largest integer is "3".
```

**Example 2:**
```
Input: nums = ["2","21","12","1"], k = 3
Output: "2"
Explanation: The numbers sorted in non-decreasing order are ["1","2","12","21"].
The 3rd largest integer is "2".
```

**Example 3:**
```
Input: nums = ["0","0"], k = 2
Output: "0"
Explanation: The numbers sorted in non-decreasing order are ["0","0"].
The 2nd largest integer is "0".
```

**Constraints:**
- `1 <= k <= nums.length <= 10^4`
- `1 <= nums[i].length <= 100`
- `nums[i]` consists of only digits
- `nums[i]` will not have any leading zeros

## Observations

1. **String to Integer Conversion**: The problem provides numbers as strings, but we need to compare them numerically, not lexicographically. For example, `"9"` is greater than `"10"` lexicographically, but numerically `10 > 9`.

2. **Kth Largest vs Kth Smallest**: Finding the kth largest element is equivalent to finding the (n-k+1)th smallest element in an array of size n.

3. **Min-Heap Approach**: We can use a min-heap of size k to efficiently find the kth largest element:
   - Keep only the k largest elements in the heap
   - The root of the min-heap will be the kth largest element
   - As we maintain only k elements, the smallest of these k elements is the kth largest overall

4. **Time Complexity Consideration**: 
   - Converting all strings to integers: O(n)
   - Heapifying: O(n)
   - Popping (n-k) elements: O((n-k) log k)
   - Overall: O(n + (n-k) log k)

5. **Space Complexity**: O(n) for storing the heap initially (though it gets reduced to k elements)

## Solution

### Approach: Min-Heap with Size K

The solution uses a min-heap to efficiently find the kth largest element:

**Algorithm:**
1. Convert all string numbers to integers and create a list
2. Heapify the list to create a min-heap
3. Pop elements from the heap until only k elements remain
4. The root of the heap (smallest among the k largest) is the kth largest element

**Why This Works:**
- A min-heap keeps the smallest element at the root
- By removing the smallest elements until only k remain, we're left with the k largest elements
- The smallest among these k largest elements is exactly the kth largest element

**Code:**
```python
import heapq

class Solution:
    def kthLargestNumber(self, nums: List[str], k: int) -> str:
        # Convert strings to integers
        pq = [int(val) for val in nums]
        
        # Create a min-heap
        heapq.heapify(pq)
        
        # Remove smallest elements until k elements remain
        while len(pq) > k:
            heapq.heappop(pq)
        
        # The root is now the kth largest element
        return str(pq[0])
```

**Step-by-Step Example:**
For `nums = ["3","6","7","10"], k = 4`:
1. Convert to integers: `[3, 6, 7, 10]`
2. Heapify (already a valid min-heap): `[3, 6, 7, 10]`
3. `len(pq) = 4, k = 4`, so no popping needed
4. Return `str(pq[0])` = `"3"`

For `nums = ["2","21","12","1"], k = 3`:
1. Convert to integers: `[2, 21, 12, 1]`
2. Heapify: `[1, 2, 12, 21]`
3. Pop once: `[2, 21, 12]` (removed 1)
4. After restructuring: `[2, 21, 12]` with 2 at root
5. Return `"2"`

**Complexity Analysis:**
- **Time Complexity:** O(n + (n-k) log k)
  - Converting strings to integers: O(n)
  - Heapifying: O(n)
  - Popping (n-k) elements: O((n-k) log k)
- **Space Complexity:** O(n) for the heap

**Alternative Approaches:**
1. **Sorting:** Sort the array in descending order and return the kth element. Time: O(n log n), Space: O(1) excluding sort space.
2. **Max-Heap:** Use a max-heap and pop k-1 times. Time: O(n + k log n), Space: O(n).
3. **QuickSelect:** Use the QuickSelect algorithm for average O(n) time, but worst case O(n²).

# Tags

`Heap`, `Min-Heap`, `Priority Queue`, `Kth Largest Element`, `Array`, `Sorting`

