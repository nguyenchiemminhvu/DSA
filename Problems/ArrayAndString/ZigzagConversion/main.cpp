/**
https://leetcode.com/problems/zigzag-conversion/description/

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
 

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
Example 3:

Input: s = "A", numRows = 1
Output: "A"
 

Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000
*/

#include <iostream>
#include <vector>
#include <string>
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
    string convert(const string& s, int numRows)
    {
        int numCols = (s.length() / numRows) + 1;

        std::vector<std::vector<char>> mat(1001, std::vector<char>(1001, ' '));

        int is = 0;
        int r = 0;
        int c = 0;
        bool moving_down = true;
        while (is < s.length())
        {
            mat[r][c] = s[is++];

            if (r == 0)
            {
                moving_down = true;
            }
            else if (r == numRows - 1)
            {
                moving_down = false;
            }

            if (moving_down)
            {
                r++;
            }
            else
            {
                r--;
                c++;
            }
        }

        std::string res;
        for (const std::vector<char>& line : mat)
        {
            for (char c : line)
            {
                if (c != ' ')
                {
                    res += c;
                }
            }

            if (res.length() >= s.length())
            {
                break;
            }
        }
        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.convert("PAYPALISHIRING", 3) << std::endl;
    return 0;
}