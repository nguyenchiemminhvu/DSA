/**
https://leetcode.com/problems/print-words-vertically/description/

Given a string s. Return all the words vertically in the same order in which they appear in s.
Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
Each word would be put on only one column and that in one column there will be only one word.

Example 1:

Input: s = "HOW ARE YOU"
Output: ["HAY","ORO","WEU"]
Explanation: Each word is printed vertically. 
 "HAY"
 "ORO"
 "WEU"

Example 2:

Input: s = "TO BE OR NOT TO BE"
Output: ["TBONTB","OEROOE","   T"]
Explanation: Trailing spaces is not allowed. 
"TBONTB"
"OEROOE"
"   T"

Example 3:

Input: s = "CONTEST IS COMING"
Output: ["CIC","OSO","N M","T I","E N","S G","T"]

Constraints:

1 <= s.length <= 200
s contains only upper case English letters.
It's guaranteed that there is only one space between 2 words.
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<string> printVertically(const string& s)
    {
        std::vector<std::string> res;

        std::stringstream ss(s);
        std::vector<std::string> table;
        std::string temp;
        int max_length = 0;
        while (ss >> temp)
        {
            max_length = std::max(max_length, (int)temp.length());
            table.push_back(temp);
        }

        for (std::string& word : table)
        {
            if (word.length() < max_length)
            {
                word += std::string(max_length - word.length(), ' ');
            }
        }

        for (int i = 0; i < max_length; i++)
        {
            std::string temp;
            for (const std::string& row : table)
            {
                temp.push_back(row[i]);
            }
            temp = trimTrailingWhitespace(temp);
            res.push_back(temp);
        }

        return res;
    }
private:
    std::string trimTrailingWhitespace(const std::string& str)
    {
        auto end = std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base();
        return std::string(str.begin(), end);
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> res = sol.printVertically("HOW ARE YOU");
    for (const std::string& s : res)
    {
        std::cout << s << std::endl;
    }
    return 0;
}