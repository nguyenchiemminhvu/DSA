/**
https://leetcode.com/problems/iterator-for-combination/description/
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class CombinationIterator
{
public:
    CombinationIterator(string& s, int len)
    {
        int n = s.length();
        for (int mask = 0; mask < (1 << n); mask++)
        {
            int set_bit = __builtin_popcount(mask);
            if (set_bit != len)
            {
                continue;
            }

            std::string temp;
            for (int i = 0; i < 32; i++)
            {
                if ((1 << i) & mask)
                {
                    temp.push_back(s[i]);
                }
            }

            combination.push_back(temp);
        }

        std::sort(combination.begin(), combination.end());
        idx = 0;
    }
    
    string next()
    {
        return combination[idx++];
    }
    
    bool hasNext()
    {
        return idx < combination.size();
    }
private:
    std::vector<std::string> combination;
    int idx;
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

int main()
{
    string characters = "abc";
    int combinationLength = 2;
    CombinationIterator* obj = new CombinationIterator(characters, combinationLength);

    while (obj->hasNext())
    {
        cout << obj->next() << endl;
    }

    delete obj;
    return 0;
}