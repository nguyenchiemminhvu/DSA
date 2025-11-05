from typing import List

class Solution:
    def addToArrayForm(self, num: List[int], k: int) -> List[int]:
        nk = [ord(c) - ord('0') for c in str(k)]
        a = num[::-1]
        b = nk[::-1]
        if len(a) < len(b):
            a, b = b, a
        na = len(a)
        nb = len(b)
        b.extend([0] * (na - nb))
        ia = 0
        ib = 0
        carry = 0
        while ia < na:
            temp = a[ia] + b[ib] + carry
            carry = temp // 10
            temp %= 10
            a[ia] = temp
            ia += 1
            ib += 1
        
        if carry == 1:
            a.append(1)
        return a[::-1]