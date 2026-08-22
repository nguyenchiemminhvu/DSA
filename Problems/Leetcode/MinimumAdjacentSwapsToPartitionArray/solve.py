def count_adjacent_swaps(arr):
    def merge_and_count(arr, temp, left, right):
        inv_count = 0
        if left < right:
            mid = (left + right) // 2
            inv_count += merge_and_count(arr, temp, left, mid)
            inv_count += merge_and_count(arr, temp, mid + 1, right)
            inv_count += merge(arr, temp, left, mid, right)
        return inv_count

    def merge(arr, temp, left, mid, right):
        i = left     # Left subarray index
        j = mid + 1  # Right subarray index
        k = left     # Result subarray index
        inv_count = 0

        while i <= mid and j <= right:
            if arr[i] <= arr[j]:
                temp[k] = arr[i]
                i += 1
            else:
                # Inversion found! 
                # Since left array is sorted, arr[i] thru arr[mid] are all > arr[j]
                temp[k] = arr[j]
                inv_count += (mid - i + 1)
                j += 1
            k += 1

        while i <= mid:
            temp[k] = arr[i]
            i += 1
            k += 1

        while j <= right:
            temp[k] = arr[j]
            j += 1
            k += 1

        for loop_var in range(left, right + 1):
            arr[loop_var] = temp[loop_var]

        return inv_count

    temp_arr = [0] * len(arr)
    return merge_and_count(arr, temp_arr, 0, len(arr) - 1)

class Solution:
    def minAdjacentSwaps(self, nums: list[int], a: int, b: int) -> int:
        for i, val in enumerate(nums):
            if val < a:
                nums[i] = 0
            elif val > b:
                nums[i] = 2
            else:
                nums[i] = 1
        
        return count_adjacent_swaps(nums) % (10**9 + 7)