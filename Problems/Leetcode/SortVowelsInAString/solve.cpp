#include <iostream>
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
    string sortVowels(string& s)
    {
        const std::string vowels = "AEIOUaeiou";
        auto f_is_vowel = [&](char c) {
            return vowels.find(c) != std::string::npos;
        };

        std::vector<int> counter(128, 0);
        for (char c : s)
        {
            if (f_is_vowel(c))
            {
                counter[c]++;
            }
        }

        int iv = 0;
        for (char& c : s)
        {
            if (f_is_vowel(c))
            {
                while (iv < vowels.length() && counter[vowels[iv]] <= 0)
                {
                    iv++;
                }
                c = vowels[iv];
                counter[vowels[iv]]--;
            }
        }

        return s;
    }
};

int main()
{
    Solution solution;
    string s = "lEetcOde";
    cout << solution.sortVowels(s) << endl;
    return 0;
}