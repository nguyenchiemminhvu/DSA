## Problem

https://leetcode.com/problems/the-skyline-problem/description/

```
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.

The geometric information of each building is given in the array buildings where buildings[i] = [lefti, righti, heighti]:

lefti is the x coordinate of the left edge of the ith building.
righti is the x coordinate of the right edge of the ith building.
heighti is the height of the ith building.
You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.

Note: There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...]

Example 1:

Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
Explanation:
Figure A shows the buildings of the input.
Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.

Example 2:

Input: buildings = [[0,2,3],[2,5,3]]
Output: [[0,3],[5,0]]

Constraints:

1 <= buildings.length <= 104
0 <= lefti < righti <= 231 - 1
1 <= heighti <= 231 - 1
buildings is sorted by lefti in non-decreasing order.
```

## Observations

1. **Key Points Definition**: A key point in the skyline represents a position where the height changes. We need to track where buildings start (height increases) and end (height decreases).

2. **Critical Events**: Each building contributes two critical events:
   - Left edge (start): A potential height increase at position `left`
   - Right edge (end): A potential height decrease at position `right`

3. **Overlapping Buildings**: When multiple buildings overlap, the skyline height at any position is determined by the tallest building at that position.

4. **Merging Requirement**: The problem can be solved using divide and conquer:
   - Break down buildings into smaller groups
   - Compute skyline for each group
   - Merge skylines together while maintaining the maximum height rule

5. **No Consecutive Same Heights**: The output should not have consecutive horizontal segments of the same height. When merging, we skip adding a point if it has the same height as the previous point.

6. **Complexity Considerations**:
   - A brute force approach would check every position, which is inefficient
   - Divide and conquer reduces the problem to O(n log n) complexity
   - Each merge operation is O(n) where n is the number of contour points

## Solution

### Approach: Divide and Conquer

The solution uses a divide and conquer strategy similar to merge sort:

**1. Base Case (Single Building)**
   - For a single building `[left, right, height]`, create two contour points:
     - `[left, height]`: Building starts, height goes up
     - `[right, 0]`: Building ends, height goes back to ground level

**2. Divide Step**
   - Split the buildings array into two halves
   - Recursively compute the skyline (contour) for each half

**3. Conquer Step (Merge)**
   - Merge two skylines by processing their contour points in order of x-coordinate
   - At each position, track the current height from both left and right skylines
   - The actual height at any position is the maximum of the two heights
   - Only add a point to the merged result if the height changes

**Key Insights for Merging:**

```
When processing contour points from two skylines:
- Maintain two variables: left_height and right_height
- When we encounter a point from the left skyline: update left_height
- When we encounter a point from the right skyline: update right_height
- The actual height at that position = max(left_height, right_height)
- Only add to result if this height differs from the previous height
```

**Example Walkthrough:**

For buildings `[[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]`:

1. Split into smaller groups and process recursively
2. Building `[2,9,10]` → Contour: `[[2,10], [9,0]]`
3. Building `[3,7,15]` → Contour: `[[3,15], [7,0]]`
4. Merge these two:
   - At x=2: left_height=10, right_height=0 → max=10 → Add `[2,10]`
   - At x=3: left_height=10, right_height=15 → max=15 → Add `[3,15]`
   - At x=7: left_height=10, right_height=0 → max=10 (skip, duplicate height)
   - At x=9: left_height=0, right_height=0 → max=0
5. Continue merging with remaining buildings...

**Time Complexity:** O(n log n)
- Dividing: O(log n) levels
- Merging at each level: O(n) total work per level
- Total: O(n log n)

**Space Complexity:** O(n)
- Recursion stack: O(log n)
- Storage for contours: O(n)

**Alternative Approaches:**
1. **Heap/Priority Queue**: Track active buildings at each critical point using a max heap
2. **Sweep Line**: Sort all events and process them left to right while maintaining active buildings

## Tags

array, backtracking, divide and conquer