class Solution:
    def categorizeBox(self, l: int, w: int, h: int, m: int) -> str:
        bulky = False
        heavy = False
        if any(val >= 10**4 for val in [l, w, h]) or l * w * h >= 10**9:
            bulky = True
        if m >= 100:
            heavy = True
        
        if bulky and heavy:
            return "Both"
        if not bulky and not heavy:
            return "Neither"
        if bulky:
            return "Bulky"
        return "Heavy"