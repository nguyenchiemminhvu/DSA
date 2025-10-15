#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int splitNum(int num)
    {
        std::string s = std::to_string(num);
        std::sort(s.begin(), s.end());
        int n = s.length();
        std::string n1 = "";
        std::string n2 = "";
        for (int i = 0; i < n; i += 2)
        {
            n1 += s[i];
        }
        for (int i = 1; i < n; i += 2)
        {
            n2 += s[i];
        }

        return std::stoi(n1) + std::stoi(n2);
    }
};

int main()
{
    Solution sol;
    int num = 2932;
    int result = sol.splitNum(num);
    std::cout << "The minimum sum after splitting " << num << " is: " << result << std::endl;
    return 0;
}