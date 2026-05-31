## Problem

https://leetcode.com/problems/destroying-asteroids/description/

You are given an integer `mass`, the original mass of a planet, and an integer array `asteroids` where `asteroids[i]` is the mass of the `i`th asteroid.

You can arrange for the planet to collide with the asteroids in **any arbitrary order**. If the planet's mass is **greater than or equal to** an asteroid's mass, the asteroid is destroyed and the planet gains that mass. Otherwise, the planet is destroyed.

Return `true` if **all** asteroids can be destroyed, otherwise return `false`.

---

## Observations

1. **Order matters greedily.** The planet must absorb smaller asteroids first to grow large enough to handle bigger ones. Tackling a large asteroid too early risks planet destruction.

2. **Sorting is optimal.** If we sort asteroids in ascending order, we ensure the planet is always as large as possible before facing the next asteroid. Any other order could introduce a failure that sorted order would have avoided.

3. **No backtracking needed.** Once sorted, a single linear pass is sufficient — if the planet cannot destroy an asteroid in sorted order, it can never destroy it in any order (the planet would never be larger at that point than it is after absorbing all smaller ones).

4. **Integer overflow risk.** The planet mass accumulates, so large inputs may require a 64-bit integer. In Python this is handled automatically.

---

## Solution

```python
class Solution:
    def asteroidsDestroyed(self, mass: int, other_masses: List[int]) -> bool:
        other_masses.sort()
        for val in other_masses:
            if mass >= val:
                mass += val
            else:
                return False
        return True
```

**Step-by-step:**

1. Sort `other_masses` in ascending order so the planet always faces the smallest remaining asteroid next.
2. Iterate through each asteroid:
   - If `mass >= val`, the asteroid is destroyed and the planet grows: `mass += val`.
   - Otherwise, the planet cannot destroy this asteroid even after absorbing all smaller ones — return `False`.
3. If all asteroids are absorbed, return `True`.

**Complexity:**
- Time: $O(n \log n)$ — dominated by sorting.
- Space: $O(1)$ extra (in-place sort).
