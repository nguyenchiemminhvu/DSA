# https://leetcode.com/problems/finding-pairs-with-a-certain-sum/description/

from collections import Counter

class FindSumPairs:
    def __init__(self, nums1: List[int], nums2: List[int]):
        self.__arr1 = nums1
        self.__arr2 = nums2
        self.__freq2 = Counter(nums2)

    def add(self, index: int, val: int) -> None:
        self.__freq2[self.__arr2[index]] -= 1
        self.__arr2[index] += val
        self.__freq2[self.__arr2[index]] += 1

    def count(self, tot: int) -> int:
        res = 0
        for val in self.__arr1:
            res += self.__freq2[tot - val]
        return res

# Your FindSumPairs object will be instantiated and called as such:
# obj = FindSumPairs(nums1, nums2)
# obj.add(index,val)
# param_2 = obj.count(tot)

if __name__ == "__main__":
    nums1 = [1, 2, 3]
    nums2 = [4, 5, 6]
    obj = FindSumPairs(nums1, nums2)
    print(obj.count(7))  # Output: 3 (pairs: (1,6), (2,5), (3,4))
    obj.add(0, 1)        # nums2 becomes [5, 5, 6]
    print(obj.count(7))  # Output: 2 (pairs: (1,6), (2,5))