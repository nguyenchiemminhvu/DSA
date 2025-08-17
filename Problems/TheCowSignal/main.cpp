/**
Bessie and her cow friends are playing as their favorite cow superheroes. Of course, everyone knows that any self-respecting superhero needs a signal to call them to action. 
Bessie has drawn a special signal on a sheet but this is too small, much too small! Bessie wants to amplify the signal so it is exactly K times bigger
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    std::vector<std::string> makeKTimesBigger(const std::vector<std::string>& origin, int k)
    {
        int m = origin.size();
        std::vector<std::string> res;
        for (int i = 0; i < m; i++)
        {
            std::string row;
            for (char c : origin[i])
            {
                std::string temp(k, c);
                row.insert(row.end(), temp.begin(), temp.end());
            }
            
            for (int j = 0; j < k; j++)
            {
                res.push_back(row);
            }
        }

        return res;
    }
};

int main()
{
    freopen("cowsignal.in", "r", stdin);
    freopen("cowsignal.out", "w", stdout);

    int m, n, k;
    std::cin >> m >> n >> k;
    std::vector<std::string> signal;
    for (int i = 0; i < m; i++)
    {
        std::string temp;
        std::cin >> temp;
        signal.push_back(temp);
    }

    Solution sol;
    signal = sol.makeKTimesBigger(signal, k);
    for (const std::string& row : signal)
    {
        std::cout << row << std::endl;
    }
    return 0;
}