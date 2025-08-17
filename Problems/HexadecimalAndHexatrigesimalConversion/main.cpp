// https://leetcode.com/problems/hexadecimal-and-hexatrigesimal-conversion/description/

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Solution
{
public:
    string concatHex36(int n)
    {
        return to_hexadecimal(n * n) + to_hexatrigesimal(n * n * n);
    }
private:
    std::string to_hexadecimal(int n)
    {
        if (n < 0)
        {
            return "";
        }

        std::string res;
        while (n)
        {
            int m = n % 16;
            if (m <= 9)
            {
                res.push_back('0' + m);
            }
            else
            {
                res.push_back('A' + m - 10);
            }
            n /= 16;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
    
    std::string to_hexatrigesimal(int n)
    {
        if (n < 0)
        {
            return "";
        }

        std::string res;
        while (n)
        {
            int m = n % 36;
            if (m <= 9)
            {
                res.push_back('0' + m);
            }
            else
            {
                res.push_back('A' + m - 10);
            }
            n /= 36;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
};

int main()
{
    Solution sol;
    cout << sol.concatHex36(10) << endl;

    return 0;
}