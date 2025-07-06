// https://leetcode.com/problems/finding-pairs-with-a-certain-sum/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class FindSumPairs
{
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2)
    {
        arr1.swap(nums1);
        arr2.swap(nums2);
        for (int val : arr2)
        {
            freq2[val]++;
        }
    }
    
    void add(int index, int val)
    {
        freq2[arr2[index]]--;
        arr2[index] += val;
        freq2[arr2[index]]++;
    }
    
    int count(int tot)
    {
        int res = 0;
        for (int val : arr1)
        {
            res += freq2[tot - val];
        }
        return res;
    }
private:
    std::vector<int> arr1;
    std::vector<int> arr2;
    std::unordered_map<int, int> freq2;
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */

int main()
{
    vector<int> nums1 = {1, 2, 3};
    vector<int> nums2 = {4, 5, 6};
    
    FindSumPairs* obj = new FindSumPairs(nums1, nums2);
    cout << obj->count(7) << endl; // Output: 3
    obj->add(0, 1); // nums2 becomes [5, 5, 6]
    cout << obj->count(7) << endl; // Output: 2
    
    delete obj;
    return 0;
}