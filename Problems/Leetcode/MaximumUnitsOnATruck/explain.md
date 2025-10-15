## Problem

https://leetcode.com/problems/maximum-units-on-a-truck/

```
You are assigned to put some amount of boxes onto one truck. You are given a 2D array boxTypes, where boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]:

numberOfBoxesi is the number of boxes of type i.
numberOfUnitsPerBoxi is the number of units in each box of the type i.
You are also given an integer truckSize, which is the maximum number of boxes that can be put on the truck. You can choose any boxes to put on the truck as long as the number of boxes does not exceed truckSize.

Return the maximum total number of units that can be put on the truck.

Example 1:

Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
Output: 8
Explanation: There are:
- 1 box of the first type that contains 3 units.
- 2 boxes of the second type that contain 2 units each.
- 3 boxes of the third type that contain 1 unit each.
You can take all the boxes of the first and second types, and one box of the third type.
The total number of units will be = (1 * 3) + (2 * 2) + (1 * 1) = 8.

Example 2:

Input: boxTypes = [[5,10],[2,5],[4,7],[3,9]], truckSize = 10
Output: 91

Constraints:

1 <= boxTypes.length <= 1000
1 <= numberOfBoxesi, numberOfUnitsPerBoxi <= 1000
1 <= truckSize <= 106
```

## Observations

1. **Greedy Approach**: To maximize the total number of units, we should prioritize boxes with higher units per box first. This is a classic greedy optimization problem.

2. **Sorting Strategy**: We need to sort the `boxTypes` array in descending order based on `numberOfUnitsPerBox` (second element of each subarray).

3. **Capacity Constraint**: We have a limited truck capacity (`truckSize`), so we need to be careful not to exceed it while selecting boxes.

4. **Partial Selection**: We might not be able to take all boxes of a certain type if it would exceed the truck capacity. In such cases, we take as many as possible from that type.

5. **Optimal Substructure**: At each step, taking the maximum units per box available is the locally optimal choice that leads to the globally optimal solution.

## Solution

1. **Sort**: First, sort `boxTypes` by units per box in descending order. This ensures we always consider the most valuable boxes first.

2. **Greedy Selection**: Iterate through the sorted box types and for each type:
   - Calculate how many boxes we can take: `min(available_boxes, remaining_capacity)`
   - Add the units from these boxes to our result
   - Update the remaining truck capacity
   - Move to the next box type

3. **Termination**: Stop when either the truck is full (`truckSize = 0`) or we've considered all box types.

**Time Complexity**: O(n log n) due to sorting, where n is the number of box types.
**Space Complexity**: O(1) if we don't count the space used by sorting (which is typically O(log n) for in-place sorting algorithms).

**Example Walkthrough** (boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4):
1. After sorting: [[1,3],[2,2],[3,1]] (already sorted by units per box)
2. Take 1 box of type [1,3]: res = 3, truckSize = 3
3. Take 2 boxes of type [2,2]: res = 3 + 4 = 7, truckSize = 1
4. Take 1 box of type [3,1]: res = 7 + 1 = 8, truckSize = 0
5. Return 8

## Tags

array, greedy