#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    string removeOccurrences(string& s, string& part)
    {
        size_t found = std::string::npos;
        while (s.length() > 0 && (found = s.find(part)) != std::string::npos)
        {
            s.erase(found, part.length());
        }
        return s;
    }
};

int main()
{
    Solution solution;
    string s = "daabcbaabcbc";
    string part = "abc";
    string result = solution.removeOccurrences(s, part);
    cout << result << endl;  // Output: "dab"
    return 0;
}