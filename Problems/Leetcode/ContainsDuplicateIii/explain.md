## Problem

https://leetcode.com/problems/contains-duplicate-iii/description/

Given an integer array `nums` and two integers `indexDiff` and `valueDiff`, find a pair of indices `(i, j)` such that:
- `i != j`
- `abs(i - j) <= indexDiff`
- `abs(nums[i] - nums[j]) <= valueDiff`

Return `true` if such a pair exists, `false` otherwise.

---

## Observations

1. **Brute force** would be O(n × indexDiff) — for each element, scan the previous `indexDiff` elements. Too slow for large inputs.

2. We need a **sliding window** of size `indexDiff` to enforce the index constraint. As we move forward, we add the new element and evict the element that fell out of the window.

3. The tricky part is the **value constraint**: among elements in the window, check if any two are within `valueDiff` of each other. We need this check to be fast (O(1) or O(log n)).

4. **Key insight — Bucket Sort trick:**  
   If we divide the number line into buckets of width `w = valueDiff + 1`, then:
   - Two numbers in the **same bucket** are guaranteed to satisfy `abs(a - b) < w = valueDiff + 1`, i.e. `abs(a - b) <= valueDiff`. ✅
   - Two numbers in **adjacent buckets** *might* satisfy the condition — we need an explicit check.
   - Two numbers in buckets **more than 1 apart** can never satisfy the condition. ✅

5. Because `w = valueDiff + 1`, each bucket holds **at most one element** from the current sliding window. If a bucket already has an element and we try to insert another, they must be within `valueDiff` — immediate match.

6. **Handling negative numbers:** Python's `//` is floor division, so negative numbers map correctly to negative bucket IDs (e.g. `-7 // 3 = -3`). This works naturally.

---

## Solution Explanation

```python
class Solution:
    def containsNearbyAlmostDuplicate(self, nums: List[int], indexDiff: int, valueDiff: int) -> bool:
        if valueDiff < 0: 
            return False
            
        buckets = {}
        # Width of each bucket
        w = valueDiff + 1
        
        for i, num in enumerate(nums):
            # Map number to its bucket ID
            bucket_id = num // w
            
            # Check current bucket
            if bucket_id in buckets:
                return True
                
            # Check adjacent lower bucket
            if (bucket_id - 1) in buckets and abs(num - buckets[bucket_id - 1]) <= valueDiff:
                return True
                
            # Check adjacent higher bucket
            if (bucket_id + 1) in buckets and abs(num - buckets[bucket_id + 1]) <= valueDiff:
                return True
                
            # Add to bucket
            buckets[bucket_id] = num
            
            # Evict old element outside window
            if i >= indexDiff:
                del buckets[nums[i - indexDiff] // w]
                
        return False
```

### Step-by-step walkthrough

| Step | Action | Why |
|------|--------|-----|
| Set `w = valueDiff + 1` | Define bucket width | Numbers in the same bucket differ by at most `valueDiff` |
| `bucket_id = num // w` | Assign element to bucket | Groups nearby values together |
| Check `bucket_id` in `buckets` | Same bucket → guaranteed match | Any two values in same bucket differ by < w |
| Check `bucket_id ± 1` | Adjacent bucket → possible match | Values could straddle a bucket boundary; explicit check needed |
| `buckets[bucket_id] = num` | Store element in its bucket | At most one element per bucket in the window |
| Evict when `i >= indexDiff` | Maintain window of size `indexDiff` | Remove element that is now too far away by index |

### Why only check ±1 adjacent buckets?

The number line is partitioned as: `[0, w), [w, 2w), [2w, 3w), ...`

If `num` is in bucket `k`, it lies in range `[k*w, (k+1)*w)`.  
For another number `x` to satisfy `abs(num - x) <= valueDiff = w - 1`, `x` must lie in `[num - (w-1), num + (w-1)]`.  
This range spans at most 3 consecutive buckets: `k-1`, `k`, and `k+1`.  
So checking only the current and two adjacent buckets is sufficient.

### Complexity

- **Time:** O(n) — each element is inserted and deleted from the hash map at most once; all bucket lookups are O(1).
- **Space:** O(min(n, indexDiff)) — the sliding window holds at most `indexDiff + 1` elements.

---

## Examples Traced

**Example 1:** `nums = [1,2,3,1]`, `indexDiff = 3`, `valueDiff = 0`  
`w = 1`, so `bucket_id = num` itself.

| i | num | bucket_id | buckets before check | result |
|---|-----|-----------|----------------------|--------|
| 0 | 1   | 1         | {}                   | add {1:1} |
| 1 | 2   | 2         | {1:1}                | add {1:1, 2:2} |
| 2 | 3   | 3         | {1:1, 2:2}           | add {1:1, 2:2, 3:3} |
| 3 | 1   | 1         | {1:1, 2:2, 3:3}      | bucket 1 exists → **return True** ✅ |

**Example 2:** `nums = [1,5,9,1,5,9]`, `indexDiff = 2`, `valueDiff = 3`  
`w = 4`, bucket IDs: `1//4=0`, `5//4=1`, `9//4=2`.

| i | num | bucket_id | action |
|---|-----|-----------|--------|
| 0 | 1   | 0         | add {0:1} |
| 1 | 5   | 1         | check 0→\|5-1\|=4 > 3, check 2→not found; add {0:1,1:5} |
| 2 | 9   | 2         | check 1→\|9-5\|=4 > 3, check 3→not found; add {0:1,1:5,2:9}; evict nums[0]=1 → del bucket 0 |
| 3 | 1   | 0         | check -1→not found, check 1→\|1-5\|=4 > 3; add {1:5,2:9,0:1}; evict nums[1]=5 → del bucket 1 |
| 4 | 5   | 1         | check 0→\|5-1\|=4 > 3, check 2→\|5-9\|=4 > 3; add {2:9,0:1,1:5}; evict nums[2]=9 → del bucket 2 |
| 5 | 9   | 2         | check 1→\|9-5\|=4 > 3, check 3→not found; add; **return False** ✅ |

