## Problem

https://leetcode.com/problems/next-greater-element-i/

```
The next greater element of some element x in an array is the first greater element that is to the right of x in the same array.

You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.

For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2. If there is no next greater element, then the answer for this query is -1.

Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.

Example 1:

Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
- 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
- 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.

Example 2:

Input: nums1 = [2,4], nums2 = [1,2,3,4]
Output: [3,-1]
Explanation: The next greater element for each value of nums1 is as follows:
- 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
- 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.

Constraints:

1 <= nums1.length <= nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 104
All integers in nums1 and nums2 are unique.
All the integers of nums1 also appear in nums2.
 
Follow up: Could you find an O(nums1.length + nums2.length) solution?
```

## Observations

1. **Problem Structure**: We need to find the next greater element for each element in `nums1`, but the search happens in `nums2`.

2. **Key Insight**: Since `nums1` is a subset of `nums2`, we can:
   - Pre-compute the next greater element for every element in `nums2`
   - Use this precomputed information to answer queries for `nums1`

3. **Monotonic Stack Pattern**: The "next greater element" problem is a classic use case for monotonic decreasing stack:
   - Process elements from right to left
   - Maintain a stack of indices where corresponding elements are in decreasing order
   - For each element, pop smaller elements from stack (they won't be "next greater" for future elements)
   - The top of stack (if exists and greater) is the next greater element

4. **Optimization**: Instead of finding next greater element for each `nums1[i]` individually (O(n₁×n₂)), we can:
   - Process `nums2` once to build next greater mapping: O(n₂)
   - Answer all `nums1` queries using the mapping: O(n₁)
   - Total complexity: O(n₁ + n₂)

## Solution

**Phase 1: Build Next Greater Mapping for nums2**
- Traverse `nums2` from right to left
- Use monotonic decreasing stack to efficiently find next greater elements
- Store results in `prefix` array where `prefix[i]` = index of next greater element for `nums2[i]`
- Build value-to-index mapping in dictionary `d`

**Phase 2: Answer Queries for nums1**
- For each element in `nums1`, find its position in `nums2` using dictionary
- Use precomputed `prefix` array to get next greater element index
- Convert index back to actual value for the result

### Example Walkthrough:
```
nums1 = [4,1,2], nums2 = [1,3,4,2]

Processing nums2 from right to left:
i=3: nums2[3]=2, stack=[], prefix[3]=-1, stack=[3]
i=2: nums2[2]=4, stack=[3], 2<4 so pop 3, stack=[], prefix[2]=-1, stack=[2]  
i=1: nums2[1]=3, stack=[2], 3<4 so prefix[1]=2, stack=[2,1]
i=0: nums2[0]=1, stack=[2,1], 1<3 so prefix[0]=1, stack=[2,1,0]

prefix = [1, 2, -1, -1]  // indices of next greater elements
d = {1:0, 3:1, 4:2, 2:3} // value to index mapping

For nums1:
- nums1[0]=4: d[4]=2, prefix[2]=-1 → res[0]=-1
- nums1[1]=1: d[1]=0, prefix[0]=1, nums2[1]=3 → res[1]=3  
- nums1[2]=2: d[2]=3, prefix[3]=-1 → res[2]=-1

Result: [-1, 3, -1]
```

### Time Complexity: O(n₁ + n₂)
- Processing nums2: O(n₂) - each element pushed/popped from stack at most once
- Processing nums1: O(n₁) - constant time lookup per element

### Space Complexity: O(n₂)
- Stack: O(n₂) in worst case
- Dictionary and prefix array: O(n₂)

# Tags
Stack, Monotonic Stack, Hash Table, Array

