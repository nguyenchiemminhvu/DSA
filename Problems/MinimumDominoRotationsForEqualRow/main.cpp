// https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms)
    {
        int res = INT_MAX;
        int n = tops.size();

        // Try to make all values equal to tops[0]
        if (canMake(tops[0], tops, bottoms, res))
            return res;

        // Try to make all values equal to bottoms[0]
        res = INT_MAX; // reset
        if (canMake(bottoms[0], tops, bottoms, res))
            return res;

        return -1;
    }

private:
    bool canMake(int target, vector<int>& tops, vector<int>& bottoms, int& res)
    {
        int n = tops.size();
        int top_swaps = 0, bottom_swaps = 0;

        for (int i = 0; i < n; i++)
        {
            if (tops[i] != target && bottoms[i] != target)
                return false;

            if (tops[i] != target)
                top_swaps++;
            if (bottoms[i] != target)
                bottom_swaps++;
        }

        res = std::min(top_swaps, bottom_swaps);
        return true;
    }
};

int main()
{
    Solution sol;
    vector<int> tops = {2, 1, 2, 4, 2, 2};
    vector<int> bottoms = {5, 2, 6, 2, 3, 2};
    int result = sol.minDominoRotations(tops, bottoms);
    cout << "Minimum number of rotations: " << result << endl;
    return 0;
}