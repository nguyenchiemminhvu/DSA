## Problem

https://leetcode.com/problems/kth-largest-element-in-a-stream/description/

```
You are part of a university admissions office and need to keep track of the kth highest test score from applicants in real-time. This helps to determine cut-off marks for interviews and admissions dynamically as new applicants submit their scores.

You are tasked to implement a class which, for a given integer k, maintains a stream of test scores and continuously returns the kth highest test score after a new score has been submitted. More specifically, we are looking for the kth highest score in the sorted list of all scores.

Implement the KthLargest class:

KthLargest(int k, int[] nums) Initializes the object with the integer k and the stream of test scores nums.
int add(int val) Adds a new test score val to the stream and returns the element representing the kth largest element in the pool of test scores so far.

Example 1:

Input:
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]

Output: [null, 4, 5, 5, 8, 8]

Explanation:

KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3); // return 4
kthLargest.add(5); // return 5
kthLargest.add(10); // return 5
kthLargest.add(9); // return 8
kthLargest.add(4); // return 8

Example 2:

Input:
["KthLargest", "add", "add", "add", "add"]
[[4, [7, 7, 7, 7, 8, 3]], [2], [10], [9], [9]]

Output: [null, 7, 7, 7, 8]

Explanation:

KthLargest kthLargest = new KthLargest(4, [7, 7, 7, 7, 8, 3]);
kthLargest.add(2); // return 7
kthLargest.add(10); // return 7
kthLargest.add(9); // return 7
kthLargest.add(9); // return 8

Constraints:

0 <= nums.length <= 104
1 <= k <= nums.length + 1
-104 <= nums[i] <= 104
-104 <= val <= 104
At most 104 calls will be made to add.
```

## Observations

1. **Key insight**: We need to maintain the kth largest element efficiently in a stream of numbers.

2. **Min-heap approach**: Instead of storing all elements and sorting repeatedly, we can use a min-heap of size k to maintain only the k largest elements seen so far.

3. **Heap property**: In a min-heap of k elements containing the k largest values, the root (minimum element in the heap) will always be the kth largest element overall.

4. **Efficient operations**:
   - Adding a new element: O(log k)
   - Getting kth largest: O(1) - just peek at heap root
   - Space complexity: O(k) instead of O(n)

5. **Edge cases to consider**:
   - Initial array might have fewer than k elements
   - Need to maintain exactly k elements in heap after each add operation

## Solution

**Algorithm**: Use a min-heap to maintain the k largest elements.

### Approach Analysis

The provided solution has a **logical error** in the implementation. Let me explain the intended approach and the issue:

**Intended Approach:**
1. Use a min-heap to store only the k largest elements
2. When adding a new element, if heap size exceeds k, remove the smallest element
3. The root of the heap will always be the kth largest element

### How It Works

1. **Initialization**: 
   - Extract k largest elements from initial array
   - Convert to min-heap where root = kth largest

2. **Add Operation**:
   - Push new element to heap
   - If heap size > k, pop smallest element
   - Return heap root (kth largest)

### Example Walkthrough

```
k = 3, nums = [4, 5, 8, 2]
Initial heap after setup: [4, 5, 8] (min-heap)

add(3): 
  - Push 3: [3, 5, 8, 4]
  - Size > 3, pop 3: [4, 5, 8]
  - Return 4 ✓

add(5):
  - Push 5: [4, 5, 8, 5] 
  - Size > 3, pop 4: [5, 5, 8]
  - Return 5 ✓
```

### Time & Space Complexity

- **Time**: 
  - Initialization: O(n log k) where n = len(nums)
  - Add: O(log k)
- **Space**: O(k)

The key insight is maintaining only k elements instead of all n elements, making operations efficient even with large streams.

## Tags

priority queue, stream, array