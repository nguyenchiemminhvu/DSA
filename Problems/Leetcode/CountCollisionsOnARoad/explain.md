## Problem

https://leetcode.com/problems/count-collisions-on-a-road/description/

**Count Collisions on a Road**

There are `n` cars on an infinitely long road. The cars are numbered from `0` to `n - 1` from left to right and each car is present at a unique point.

You are given a 0-indexed string `directions` of length `n`. `directions[i]` can be either `'L'`, `'R'`, or `'S'` denoting whether the ith car is moving towards the left, towards the right, or staying at its current point respectively. Each moving car has the same speed.

The number of collisions can be calculated as follows:
- When two cars moving in opposite directions collide with each other, the number of collisions increases by 2.
- When a moving car collides with a stationary car, the number of collisions increases by 1.

After a collision, the cars involved can no longer move and will stay at the point where they collided. Other than that, cars cannot change their state or direction of motion.

Return the total number of collisions that will happen on the road.

**Example 1:**
```
Input: directions = "RLRSLL"
Output: 5
Explanation:
- Cars 0 and 1 collide (R meets L): collisions = 0 + 2 = 2
- Cars 2 and 3 collide (R meets S): collisions = 2 + 1 = 3
- Cars 3 and 4 collide (S meets L): collisions = 3 + 1 = 4
- Cars 4 and 5 collide (S meets L): collisions = 4 + 1 = 5
```

**Example 2:**
```
Input: directions = "LLRR"
Output: 0
Explanation: No cars will collide with each other.
```

**Constraints:**
- `1 <= directions.length <= 10^5`
- `directions[i]` is either `'L'`, `'R'`, or `'S'`

## Observations

### Key Insights

1. **Collision Patterns:**
   - `R` followed by `L` or `S`: Will collide
   - `S` or `R` followed by `L`: Will collide
   - `L` at the beginning: Never collides (moves away from all cars)
   - `R` at the end: Never collides (moves away from all cars)

2. **Collision Counting:**
   - When `R` meets `L`: Both cars stop (+2 collisions)
   - When `R` meets `S`: Moving car stops (+1 collision)
   - When `L` meets `S` or stopped car: Moving car stops (+1 collision)

3. **Chain Reactions:**
   - Multiple `R`s followed by `L` or `S`: All `R` cars will collide
   - Multiple `L`s preceded by `R` or `S`: All `L` cars will collide
   - After first collision, cars become stationary and can cause more collisions

4. **Edge Cases to Ignore:**
   - Leading `L`s: They move left away from everything (no collision)
   - Trailing `R`s: They move right away from everything (no collision)

### Algorithm Insight

The solution uses a **two-pass approach**:

**Pass 1 (Left to Right):** Count collisions from right-moving cars
- Track consecutive `R` cars
- When we hit `L` or `S`, all tracked `R` cars will collide

**Pass 2 (Right to Left):** Count collisions from left-moving cars
- Track consecutive `L` cars
- When we hit `R` or `S`, all tracked `L` cars will collide

This works because:
- Any `R` car that eventually meets an obstacle (not trailing) will collide
- Any `L` car that eventually meets an obstacle (not leading) will collide
- The two passes capture all these collisions without double-counting

## Solution

### Approach: Two-Pass Counting

**Algorithm:**

1. **First Pass (Left to Right):**
   - Maintain `count_right` to track consecutive `R` cars
   - When we encounter `R`: increment `count_right`
   - When we encounter `L` or `S`: 
     - All `count_right` cars will collide with this position
     - Add `count_right` to result
     - Reset `count_right` to 0

2. **Second Pass (Right to Left):**
   - Maintain `count_left` to track consecutive `L` cars
   - When we encounter `L`: increment `count_left`
   - When we encounter `R` or `S`:
     - All `count_left` cars will collide with this position
     - Add `count_left` to result
     - Reset `count_left` to 0

**Why This Works:**

- **First pass** counts all right-moving cars that will eventually hit something
- **Second pass** counts all left-moving cars that will eventually hit something
- Each car contributes exactly 1 to the collision count (except when R meets L directly, but this is handled correctly by both passes counting 1 each = 2 total)

**Example Walkthrough:** `"RLRSLL"`

*First Pass (L→R):*
```
Index 0: 'R' → count_right = 1
Index 1: 'L' → res += 1 (car 0 collides), count_right = 0, res = 1
Index 2: 'R' → count_right = 1
Index 3: 'S' → res += 1 (car 2 collides), count_right = 0, res = 2
Index 4: 'L' → res += 0, count_right = 0, res = 2
Index 5: 'L' → res += 0, count_right = 0, res = 2
```

*Second Pass (R→L):*
```
Index 5: 'L' → count_left = 1
Index 4: 'L' → count_left = 2
Index 3: 'S' → res += 2 (cars 4,5 collide), count_left = 0, res = 4
Index 2: 'R' → res += 0, count_left = 0, res = 4
Index 1: 'L' → count_left = 1
Index 0: 'R' → res += 1 (car 1 collides), count_left = 0, res = 5
```

**Total:** 5 collisions ✓

### Complexity Analysis

- **Time Complexity:** O(n)
  - Two linear passes through the string
  - Each character is visited exactly twice

- **Space Complexity:** O(1)
  - Only using a few variables for counting
  - No additional data structures

# Tags
- **Array**
- **String**
- **Two Pointers**
- **Simulation**
- **Greedy**

