/**
https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/description/
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles)
    {
        std::vector<std::pair<int, int>> hor;
        std::vector<std::pair<int, int>> ver;

        for (const std::vector<int>& rect : rectangles)
        {
            hor.push_back({rect[0], rect[2]});
            ver.push_back({rect[1], rect[3]});
        }
        
        std::sort(hor.begin(), hor.end());
        std::vector<std::pair<int, int>> merged_hor;
        merged_hor.push_back(hor[0]);
        for (int i = 1; i < hor.size(); i++)
        {
            if (merged_hor.back().second > hor[i].first)
            {
                merged_hor.back().second = std::max(merged_hor.back().second, hor[i].second);
            }
            else
            {
                merged_hor.push_back(hor[i]);
            }
        }

        if (merged_hor.size() >= 3)
        {
            return true;
        }

        std::sort(ver.begin(), ver.end());
        std::vector<std::pair<int, int>> merged_ver;
        merged_ver.push_back(ver[0]);
        for (int i = 1; i < ver.size(); i++)
        {
            if (merged_ver.back().second > ver[i].first)
            {
                merged_ver.back().second = std::max(merged_ver.back().second, ver[i].second);
            }
            else
            {
                merged_ver.push_back(ver[i]);
            }
        }

        if (merged_ver.size() >= 3)
        {
            return true;
        }

        return false;
    }
};

int main()
{
    Solution sol;
    int n;
    cin >> n;
    vector<vector<int>> rectangles(n, vector<int>(4));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cin >> rectangles[i][j];
        }
    }

    if (sol.checkValidCuts(n, rectangles))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}