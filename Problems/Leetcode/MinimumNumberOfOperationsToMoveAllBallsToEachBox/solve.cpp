#include <iostream>
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
    vector<int> minOperations(const string& boxes)
    {
        int n = boxes.size();
        std::vector<int> res(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (boxes[i] == '1')
            {
                for (int j = 0; j < n; j++)
                {
                    res[j] += std::abs(i - j);
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    string boxes = "001011";
    vector<int> result = sol.minOperations(boxes);
    for (int ops : result)
    {
        cout << ops << " ";
    }
    cout << endl;
    return 0;
}