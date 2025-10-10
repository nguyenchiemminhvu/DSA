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
        std::vector<int> left(n, 0);
        std::vector<int> right(n, 0);

        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && count > 0)
            {
                left[i] = left[i - 1] + count;
            }

            if (boxes[i] == '1')
                count++;
        }

        count = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (i < n - 1 && count > 0)
            {
                right[i] = right[i + 1] + count;
            }

            if (boxes[i] == '1')
                count++;
        }

        std::vector<int> res(n, 0);
        for (int i = 0; i < n; i++)
        {
            res[i] = left[i] + right[i];
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