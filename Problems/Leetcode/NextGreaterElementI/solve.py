from typing import List

class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        n1 = len(nums1)
        n2 = len(nums2)
        st = []
        prefix = [-1] * n2
        d = {}
        for i in range(n2 - 1, -1, -1):
            d[nums2[i]] = i
            while st and nums2[st[-1]] < nums2[i]:
                st.pop()
            if st and nums2[st[-1]] > nums2[i]:
                prefix[i] = st[-1]
            st.append(i)

        res = [-1] * n1
        for i in range(n1):
            if prefix[d[nums1[i]]] != -1:
                res[i] = nums2[prefix[d[nums1[i]]]]
        return res