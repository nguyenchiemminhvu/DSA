/**
 * https://leetcode.com/classic/problems/count-the-hidden-sequences/description/
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper)
    {
        std::vector<long long> arr;
        arr.push_back(0LL);
        long long mi = arr.back();
        long long ma = arr.back();
        for (long long diff : differences)
        {
            arr.push_back(arr.back() + diff);
            mi = std::min(mi, arr.back());
            ma = std::max(ma, arr.back());
        }
        
        long long range = ma - mi;
        if (upper - lower + 1 > range)
        {
            return upper - lower + 1 - range;
        }
        
        return 0;
    }
};

int main()
{
    Solution s;
    vector<int> differences = {1, -3, 4};
    int lower = 1;
    int upper = 6;
    int result = s.numberOfArrays(differences, lower, upper);
    cout << "Number of hidden sequences: " << result << endl;
    return 0;
}