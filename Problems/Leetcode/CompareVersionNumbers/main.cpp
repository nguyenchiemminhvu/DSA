#include <iostream>
#include <sstream>
#include <string>
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
    int compareVersion(const string& s1, const string& s2)
    {
        std::vector<int> l1 = split_string(s1, '.');
        std::vector<int> l2 = split_string(s2, '.');

        if (l1.size() < l2.size())
        {
            l1.insert(l1.end(), l2.size() - l1.size(), 0);
        }
        if (l1.size() > l2.size())
        {
            l2.insert(l2.end(), l1.size() - l2.size(), 0);
        }

        for (int i = 0; i < l1.size(); i++)
        {
            if (l1[i] < l2[i])
            {
                return -1;
            }
            if (l1[i] > l2[i])
            {
                return 1;
            }
        }
        
        return 0;
    }
private:
    std::vector<int> split_string(const std::string& s, char delimiter)
    {
        std::vector<int> res;
        std::stringstream ss(s);
        std::string token;

        while (std::getline(ss, token, delimiter))
        {
            res.push_back(std::stoi(token));
        }

        return res;
    }
};

int main()
{
    Solution sol;
    cout << sol.compareVersion("1.01", "1.001") << endl; // 0
    cout << sol.compareVersion("1.0", "1.0.0") << endl; // 0
    cout << sol.compareVersion("0.1", "1.1") << endl; // -1
    cout << sol.compareVersion("1.0.1", "1") << endl; // 1
    cout << sol.compareVersion("1.0.1", "1.0.1") << endl; // 0
    return 0;
}